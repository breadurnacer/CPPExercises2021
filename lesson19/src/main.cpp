#include <omp.h>

#include <vector>
#include <thread>
#include <iostream>

#include <libutils/timer.h>
#include <libutils/rasserts.h>
#include <libutils/fast_random.h>

using namespace std;


// функция создает n случайных целых чисел
std::vector<int> generateNElements(int n) {
    std::vector<int> data(n);
    FastRandom r(32458629);
    for (int i = 0; i < n; ++i) {
        data[i] = r.next(0, 10 * n);
    }
    return data;
}

// _____________________________________________________________________________________________________________________
// Эксперимент 1: поэлементное преобразование чисел

// обычная версия (какого-то по-элементного преобразования в массиве, просто какая-то формула)
void perElementProcessing(std::vector<int> &data) {
    for (int i = 0; i < data.size(); ++i) {
        data[i] = sqrtf(std::abs(data[i] * 2.0f + 23.45f));
    }
}

// многопоточная версия
void perElementProcessingOMP(std::vector<int> &data) {
#pragma omp parallel for
    for(int i=0;i<data.size();++i)
    {
        data[i]=sqrtf(std::abs(data[i] * 2.0f + 23.45f));
    }}

void test1PerElementProcessing() {
    std::cout << "Test 1: per-element processing..." << std::endl;
    int n = 10 * 1000 * 1000;
    std::vector<int> data1 = generateNElements(n); // создали N случайных целых чисел
    std::vector<int> data2 = data1;                // копия данных (чтобы каждая реализация могла работать со своими данными)

    timer t; // запускаем таймер (на самом деле это секундомер, кек)
    perElementProcessing(data1);
    double h1=t.elapsed();
    std::cout << "  Naive version:  " << t.elapsed() << " s" << std::endl; // выводим в консоль замер времени (в секундах)

    t.restart(); // перезапускаем таймер
    perElementProcessingOMP(data2);
    double h2=t.elapsed();
    std::cout << "  OpenMP version: " << t.elapsed() << " s" << std::endl;

    double speedup = (h1/h2);
    std::cout << "  OpenMP speedup: x" << speedup << std::endl;

    // сверяем результаты (а то вдруг работает быстро не результат неправильный?)
    for (int i = 0; i < n; ++i) {
        rassert(data1[i] == data2[i], 32489230409130050);
    }
    std::cout << "______________________________________________" << std::endl;
}

// _____________________________________________________________________________________________________________________
// Эксперимент 2: определение числа потоков и сумма элементов

int omp_thread_count() {
    // эта функция определяет число потоков, как это сделать проще всего?
    // попросить OpenMP запустить столько потоков сколько есть, и в каждом из потоков - увеличить счетчик на один, тем самым проверить
    int nthreads = 0;

    #pragma omp parallel // обратите внимание что это "omp parallel" а не "omp parallel for", parallel = запустить все потоки, for = распределить по ним рабочую нагрузку
    {                    // т.е. эта секция кода выполнится для каждого потока один раз, а значит увеличив счетчик nthreads на один в каждом из них - мы узнаем число потоков
        // эта секция меняет число, его нельзя менять из двух потоков одновременно,
        // поэтому секция "критическая" - т.е. выполняется одновременно только в одном потоке, а
        // остальные потоки ждут когда этот поток увеличит счетчик на один, и только затем один из них
        // тоже зайдет и увеличит счетчик на один
        #pragma omp critical
        {
            nthreads += 1;
        }
        int sum=0;
        #pragma omp parallel reduction(+: sum)
        {
            sum+=1;
        }
    }
    return nthreads;
}

void test2TotalSum() {
    std::cout << "Test 2: total sum..." << std::endl;
    int n = 10 * 1000 * 1000;
    std::vector<int> data = generateNElements(n); // создали N случайных целых чисел

    timer t; // запускаем таймер
    long long sum = 0;
    for (int i = 0; i < data.size(); ++i) {
        sum += data[i];
    }
    std::cout << "  Naive version:               " << t.elapsed() << " s" << std::endl;

    const long long sumExpected = sum; // это эталонная ожидаемая сумма с которой мы будем сверяться дальше

    {
        t.restart(); // перезапускаем таймер
        sum = 0;
        #pragma omp parallel for
        for (int i = 0; i < data.size(); ++i) {
              #pragma omp critical
            {
                sum += data[i];
            }
        }


        rassert(sum == sumExpected,
                "sum != sumExpected, sumExpected=" + std::to_string(sumExpected) + " but sum=" + std::to_string(sum));

        std::cout << "  OpenMP version+critical:     " << t.elapsed() << " s" << std::endl;
    }
        for(int iter=0;iter<5;++iter) {
        {
            t.restart(); // перезапускаем таймер
        }
            sum = 0;

        #pragma omp parallel for reduction(+: sum)
            for (int i = 0; i < data.size(); ++i) {
                sum += data[i];
            }
            rassert(sum == sumExpected,
                    "sum != sumExpected, sumExpected=" + std::to_string(sumExpected) + " but sum=" +
                    std::to_string(sum));
            std::cout << "  OpenMP version+reduction:    " << t.elapsed() << " s" << std::endl;
        }


    int nc = 0;
    int nthr = omp_thread_count();
    {
        t.restart(); // перезапускаем таймер
        sum = 0;
        #pragma omp parallel
        {
            int id = 0;
        #pragma omp critical // в критической секции рассчитаемся по номерам потоков и выведем в консоль что такой-то поток был запущен
            {
                id = nc;
                ++nc;
            }
            long long tmp = 0;
            for (int i = ((data.size() + nthr - 1) / nthr) * id;
                 i < min((int) data.size(), (int) ((data.size() + nthr - 1) / nthr) * (id + 1)); ++i) {
                tmp += data[i];
            }
        #pragma omp critical // в критической секции рассчитаемся по номерам потоков и выведем в консоль что такой-то поток был запущен
            {
                sum += tmp;
            }
        }

        rassert(sum == sumExpected,
                "sum != sumExpected, sumExpected=" + std::to_string(sumExpected) + " but sum=" +
                std::to_string(sum));
        std::cout << "  OpenMP version+my reduction: " << t.elapsed() << " s" << std::endl;
    }
    std::cout << "______________________________________________" << std::endl;
}



// _____________________________________________________________________________________________________________________
// Эксперимент 3: поиск двух наибольших различных элементов в массиве

void test3Top2ElementSearch() {
    std::cout << "Test 3: top 2 elements search using OpenMP..." << std::endl;
    int n = 100 * 1000 * 1000;
    std::vector<int> data = generateNElements(n); // создали N случайных целых чисел

    const int MIN_INT = std::numeric_limits<int>::min(); // это способ узнать какое минимальное значение есть в этом типе

    int max1 = MIN_INT; // это удобно т.к. мы ищем наибольшее число, поэтому это минимальное значение
    int max2 = MIN_INT; // является отличной оценкой снизу, любой элемент массива его сразу же заменит собой

    timer t;
    for (int i = 0; i < n; ++i) {
        int value = data[i];
        if (value > max1) { // если текущее значение больше самого большого
            max2 = max1;    // то число которое раньше было самым большим - становится вторым по величине
            max1 = value;   // а текущее значение становится самым большим
        } else {            // иначе:
            if (value > max2) { // если текущее значение больше хотя бы второго по величине
                max2 = value;   // то заменяем его
            }
        }
    }
    std::cout << "Two biggest different values: " << max1 << " and " << max2 << std::endl;
    std::cout << "  Naive version:            " << t.elapsed() << " s" << std::endl;

    const int max1Expected = max1; // будем с ними сверяться
    const int max2Expected = max2;

    max1 = MIN_INT;
    max2 = MIN_INT;
    t.restart();
    #pragma omp parallel
    {
        // TODO сделайте многопоточную версию (используйте самописную редукцию)
    }
    rassert(max1 == max1Expected && max2 == max2Expected,
            "Wrong! Expected: " + std::to_string(max1Expected) + " and " + std::to_string(max2Expected)
            + ", but " + std::to_string(max1) + " and " + std::to_string(max2) + " found!");
    std::cout << "  OpenMP+reduction version: " << t.elapsed() << " s" << std::endl;

    std::cout << "______________________________________________" << std::endl;
}

// _____________________________________________________________________________________________________________________
// Эксперимент 4: придумайте код который позволит вам экспериментально выяснить как распределяются индексы цикла по потокам
void test4HowWorkloadIsBalanced() {
    int n=1000;
    vector<int> data=generateNElements(n);
    vector<int> ans(n);
    #pragma omp parallel for
    for(int i=0;i<n;++i){
        int tid = omp_get_thread_num();
        ans[i]=tid;}
    for (int i=0;i<n;++i) {
        cout<<ans[i]<<' ';}}

int main() {
    try {
        int nthreads = omp_thread_count(); // узнали число виртуальных потоков процессора (ЦПУ) на этом компьютере
        // оно может не совпадать с числом физических вычислительных ядер ЦПУ
        // (обычно на одном ядре два виртуальных потока, см. про Hyper-Threading и SMT)
        std::cout << "CPU on this computer has " << nthreads << " virtual threads" << std::endl;
        std::cout << "______________________________________________" << std::endl;

        test1PerElementProcessing();
        test2TotalSum();
        //test3Top2ElementSearch();
        test4HowWorkloadIsBalanced();

        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}
