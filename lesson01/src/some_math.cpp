#include "some_math.h"

int fibbonachiRecursive(int n) {
    if(n==0){return 0;}
    else if(n == 1){return 1;}
    else if(n == 2){return 1;}
    else if(n > 0){
        return fibbonachiRecursive(n-1)+ fibbonachiRecursive(n-2);
    }
    else if(n<0){
        return -fibbonachiRecursive(-n);
    }
}

int fibbonachiFast(int n) {
    std::vector<int> fibonum;
    if(n==0) return 0;
    if(n==1) return 1;
    if(n==2) return 1;
    else{
        fibonum.push_back(1);
        fibonum.push_back(1);
        for(int i = 2; i<n; ++i){
            fibonum.push_back(fibonum[i-1]+fibonum[i-2]);
        }
        return fibonum[n-1];
    }
}

double solveLinearAXB(double a, double b) {
    // TODO 10 решите линейное уравнение a*x+b=0 а если решения нет - верните наибольшее значение double - найдите как это сделать в интернете по запросу "so cpp double max value" (so = stackoverflow = сайт где часто можно найти ответы на такие простые запросы), главное НЕ КОПИРУЙТЕ ПРОСТО ЧИСЛО, ПОЖАЛУЙСТААаа
    // если решений сколь угодно много - верните максимальное значение со знаком минус
    double x = 0.0;
    return x;
}

std::vector<double> solveSquare(double a, double b, double c) {
    // TODO 20 решите квадратное уравнение вида a*x^2+b*x+c=0
    // если корня два - они должны быть упорядочены по возрастанию
    std::vector<double> results;
    // чтобы добавить в вектор элемент - нужно вызвать у него метод push_back:
    results.push_back(23.9);
    return results;
}
