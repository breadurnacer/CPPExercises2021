#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

int debugPoint(int line) {
    if (line < 0)
        return 0;

    // You can put breakpoint at the following line to catch any rassert failure:
    return line;
}

#define rassert(condition, message) if (!(condition)) { std::stringstream ss; (ss << "Assertion \"" << message << "\" failed at line " << debugPoint(__LINE__) << "!"); throw std::runtime_error(ss.str()); }

const int INF = std::numeric_limits<int>::max();

struct Edge {
    int u, v; // номера вершин которые это ребро соединяет
    int w; // длина ребра (т.е. насколько длинный путь предстоит преодолеть переходя по этому ребру между вершинами)

    Edge(int u, int v, int w) : u(u), v(v), w(w)
    {}
};

struct Apex{
    int num; //номер вершины
    int distance; //кратчайшее расстояние от старта до этой точки
    int prev_apex; //номер предыдущей вершины; та, из которой мы получили кратчайшее расстояние
    bool processed; //обработана ли вершина?

    std::vector<Edge> edges; //список всех рёбер, исходящих из этой точки

    Apex(int numer){
        num = numer;
        distance = INF;
        processed = false;
        prev_apex = -1;
    }
};

std::vector<Apex> apexes; //упорядоченный список вершин
bool cmp(Apex first, Apex second) {
    return first.distance < second.distance;
}//КОМПАРАТОР ПО ВЕРШИНАМ. СОРТИРОВКА ВЕРШИН ПО ДИСТАНЦИЯМ (ПО ВОЗРАСТАНИЮ)


void run() {
    int nvertices = 0; //количество вершин
    int medges = 0; //количество ребер в графе
    std::cin >> nvertices >> medges;


    for(int i = 0; i < nvertices; ++i){
        //std::cout<< "apex" + std::to_string(i);
        apexes.push_back(Apex(i));
    }//заполняем список вершинками

    //std::vector<std::vector<Edge>> edges_by_vertex(nvertices); //список рёбер для i-той вершины
    for (int i = 0; i < medges; ++i) {
        int ai, bi, w;
        //std::cout << "ai, bi, w: ";
        std::cin >> ai >> bi >> w;
        rassert(ai >= 1 && ai <= nvertices, 23472894792020);
        rassert(bi >= 1 && bi <= nvertices, 23472894792021);
        ai -= 1;
        bi -= 1;

        Edge edgeAB(ai, bi, w);
        apexes[ai].edges.push_back(edgeAB); //обращаемся к вершине из списка, добавляем ребро в её список рёбер

        apexes[bi].edges.push_back(Edge(bi, ai, w)); // обратное ребро
    }

    const int start = 0;
    const int finish = nvertices - 1;

    apexes[start].distance = 0;

    std::vector<Apex> apexesRun; //вектор для пробежки по вершинам
    for(int i = 0; i < nvertices; ++i){
        apexesRun.push_back(apexes[i]);
        std::cout << apexesRun[i].num <<" ";
    }
    std::cout<<std::endl;

    //заполняем этот список вершинками
    //первая сортировка не требуется. всё равно начнём со стартовой (нулевой) вершины


        for(int i = start; i <= finish; ++i){ //пробегаемся по вершинам внутри списка apexesRun
            std::vector<Edge> edges_of_apex = apexesRun[i].edges; //список всех рёбер i-той вершины

            for(int j = start; j < edges_of_apex.size(); ++j){ //пробегаем по каждому ребру этой вершины
                Edge edgej = edges_of_apex[j]; //j-ое ребро
                int v = edgej.v; //номер вершины, в которую ведёт это ребро
                if(apexes[v].processed == false){
                    //проверяем, обработана ли рассматриваемая вершина

                    if(apexesRun[i].distance!=INF){
                    if(apexesRun[i].distance + edgej.w < apexes[v].distance){
                        //проверяем: меньше ли предлагаемое вершине расстояние, чем то, которое уже в ней лежит?
                        //если да, то положить предложенное расстояние
                        apexes[v].distance = apexesRun[i].distance + edgej.w;
                        apexes[v].prev_apex = apexesRun[i].num; //положить в вершину номер предыдущей "минимальной" вершины
                    }
                }}
            }
            apexesRun[i].processed = true; //вершина обработана
            //теперь из этого списка, в общем-то, его можно удалить, потому что после обработки мы её уже не рассматриваем.
            apexesRun.erase(apexesRun.begin() + i);

            //после обработки вершины, мы (вероятно) изменили значений дистанций у других вершин. а поскольку в следующем шаге надо начать
            //с вершины с наименьшей дистанцией, отсортируем массив
            std::sort(apexesRun.begin(), apexesRun.end(), cmp);
            for(int i = 0; i < apexesRun.size(); ++i){
                std::cout << apexesRun[i].num <<" ";
            }
            std::cout<<std::endl;
        }


    if (apexes[finish].prev_apex != -1) {
        std::vector<int> path;
        int x = finish;
        while(x!=-1){
            path.push_back(x);
            x = apexes[x].prev_apex;
        }

        rassert(path[0]==finish, 147862379);

        std::reverse( path.begin(), path.end() );
        rassert(path[0]==start,931709392);

        for (int i = 0; i<path.size(); ++i) {
            std::cout << (path[i] + 1) << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }
}

int main() {
    try {
        run();

        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}
