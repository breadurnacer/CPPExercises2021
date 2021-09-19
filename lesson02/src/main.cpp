#include <vector>
#include <iostream>
#include <libutils/rasserts.h>

#include "helper_function.h" // подключаем функцию print2DArray(...) из соседнего файла


void task1() {
    std::vector<int> a; // динамический массив (автоматически увеличивается по мере добавления объектов)
    a.push_back(10); // добавляем в конец число 10, тем самым увеличивая этот динамический массив
    a.push_back(11);
    a.push_back(12);
    std::cout << "current size is " << a.size() << std::endl; // печатаем в консоль текущий размер

    // чтобы продолжить выполнение задания - раскомментируйте следующие строчки - проще всего это сделать выделив их все мышкой, а затем нажать Ctrl+/ (так же можно и комментировать строки)
    rassert(a.size() > 1,3412421421); // это способ проверить некоторый факт в программе, например здесь мы ожидали бы что размер вектора 1 - давайте явно это проверим, указав код ошибки на случай если это будет не так
    rassert(a.size() == 3, "vector a should of size 3!"); // можно вместо числа писать текст описывающий проблему, но на мой взгляд это слишком долго и лениво


    a.resize(5); // изменяем размер массива, пусть он будет хранить пять чисел
    rassert(a.size() == 5, "vector a should of size 5.");
    for (int i = 0; i < 5; ++i) {
        a[i] = i; // тогда мы сможем сразу в каждую из его пяти ячеек что-то положить, например числа от 0 до 4
    }
    std::cout << "current size is " << a.size() << std::endl; // печатаем в консоль текущий размер
}

void task2() {
    std::vector<std::vector<int>> array2d; // это динамический массив в котором каждый элемент - тоже динамический массив

    rassert(array2d.size()==0, "this vector should be empty");

    std::vector<int> row0; // первый ряд чисел для нашего двумерного массива (row = ряд)
    row0.push_back(5);
    row0.push_back(8);
    row0.push_back(10);

    rassert(row0.size()==3, 329340309);

    array2d.push_back(row0);
    rassert(array2d.size()==1,23804213);

    std::cout << "print2DArray(array2d):" << std::endl;
    print2DArray(array2d);

    // теперь давайте добавим еще один ряд чисел но другим способом:
    std::vector<int> row1;
    row1.resize(3);
    row1[0] = 23;
    row1[1] = 24;
    row1[2] = 42;
    array2d.push_back(row1);

    rassert(row1.size() == 3, "row1 size should be 3");
    rassert(array2d.size() == 2, "array2d size should be 2");


    std::cout << "print2DArray(array2d):" << std::endl;
    print2DArray(array2d);

    std::vector<int> row2;
    for(int i = 0; i < 10; ++i){

        row2.push_back(i);
    }
    array2d.push_back(row2);

    print2DArray(array2d);
}

void task3() {

    int rows, cols = 0;
    std::cout << "enter rows: ";
    std::cin >> rows;
    std::cout << "enter cols: ";
    std::cin >> cols;
    rassert(rows>=1 && rows<=20, "1 <= rows <= 20");
    rassert(cols>=1 && cols<=20, "1 <= cols <= 20");

    std::vector<std::vector<int>> table;
    table.resize(rows);
    for(int i = 0; i < rows; ++i){
        table[i].resize(cols);
    }

    // TODO 37 ваша программа должна считывать пары чисел i, j в вечном цикле до тех пор пока i и j не отрицательны
    while (true) {
        int i;
        int j;
        std::cin >> i;
        std::cout << " ";
        std::cin >> j;

        rassert(i<rows,23);
        rassert(j<cols,32);

        if(i<0 || j<0) break;

        table[i][j] += 1;
        std::cout << "table now:\n";
        print2DArray(table);
        std::cout << std::endl;

        int flag1 = 1;
        for(int k = 0; k < rows; ++k){
            flag1 = 1;
            for(int l = 0; l < cols; ++l){
                if(table[k][l]!=1){
                    flag1 = 0;
                    break;
                }
            }
        }
        if(flag1 == 1){
            std::cout << "OX-XO-XO";
            break;
        }

        int flag2 = 1;
        for(int k = 0; k < cols; ++k){
            flag2 = 1;
            for(int l = 0; l < rows; ++l){
                if(table[l][k]!=1){
                    flag2 = 0;
                    break;
                }
            }
        }
        if(flag2 == 1){
            std::cout << "AX-XA-XA";
            break;
        }

  }

}


int main() {
    try {
       // task1();
        //task2();
      task3();
        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}
