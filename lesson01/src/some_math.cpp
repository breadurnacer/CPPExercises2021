#include "some_math.h"
#include <cfloat>

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
    // если решений сколь угодно много - верните максимальное значение со знаком минус
    double x = 0.0;
    if(a!=0){
        x = -b/a;
    }else{
        if (b == 0) { return -DBL_MAX; }
        if (b != 0) { return DBL_MAX; }
    }
    return x;
}

std::vector<double> solveSquare(double a, double b, double c) {
    // TODO 20 решите квадратное уравнение вида a*x^2+b*x+c=0
    std::vector<double> results;

    double D = b*b - 4*a*c;
    double x1, x2;
    if(a!=0){
    if(D>0){
        x1 = (-b - sqrt(D))/(2*a);
        x2 = (-b + sqrt(D))/(2*a);
        results.push_back(x1);
        results.push_back(x2);
    }else if(D == 0){
        results.push_back((-b)/(2*a));
    }}else{
        results.push_back(solveLinearAXB(b,c));
        return results;
    }


    // если корня два - они должны быть упорядочены по возрастанию

    // чтобы добавить в вектор элемент - нужно вызвать у него метод push_back:
    return results;
}
