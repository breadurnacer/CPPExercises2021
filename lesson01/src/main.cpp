#include <iostream> // таким образом подключаются системные библиотеки (эта нужна для вывода в консоль)
#include <vector> // подключаем библиотеку для поддержки вектора (массива динамического размера)

// таким образом подключаются наши функции
#include "simple_sum.h"
#include "some_math.h"


int main() {
    // таким образом выводятся сообщения в консоль
    // std::cout = "standard console output" = поток информации в консоль
    // std::endl = "standard end of line" = конец строчки (то же что и "\n")
    std::cout << "Hello World!" << std::endl;
    int a = 10;
    std::cout << "Please enter b=";
    int b;
    std::cin >> b; // считываем из консоли переменную
    std::cout << "b=" << b << std::endl;


    int res = sum(a, b);

    std::cout << "a+b=" << a << "+" << b << "=" << res << std::endl;


     std::cout << "fib(b)=" << fibbonachiFast(b) << std::endl;

    std::vector<double> values;
    std::cout << "values size: " << values.size() << std::endl;
    values.push_back(10);
    std::cout << "values size after push_back: " << values.size() << std::endl;
    values.push_back(20);
    values.push_back(35);
    values.push_back(4);
    std::cout << "values size after more push_back: " << values.size() << std::endl;


    for (int i = 0; i < values.size(); ++i) {
        double x = values[i];
        std::cout << x << std::endl;
    }

   while (true) {
        double a;
        std::cin >> a;
        if (a==0) {
           break;
      }
        values.push_back(a);
     }
   double sum_values = 0;
    for (int i = 0; i < values.size(); ++i) {
        double x = values[i];
        sum_values= sum_values + x;
    }
    std::cout << sum_values << std::endl;

    return 0;
}
