#include <filesystem>
#include <iostream>
#include <libutils/rasserts.h>

#include "blur.h" // TODO реализуйте функцию блюра с произвольной силой размытия в файле blur.cpp

void testSomeBlur() {
    // TODO выберите любую картинку и любую силу сглаживания - проверьте что результат - чуть размытая картинка
    // Входные картинки для тестирования возьмите из предыдущего урока (т.е. по пути lesson05/data/*).
    // Результирующие картинки сохарняйте в эту папку (т.е. по пути lesson06/resultsData/*).

    double sigma = 0.8;
    cv::Mat img = cv::imread("lesson06/data/line21_water_horizont.jpg");
    rassert(!img.empty(), 23981920813);
    cv::Mat blur_img = blur(img.clone(), sigma);
    cv::imwrite("lesson06/resultsData/line21_water_horizont_0.8.jpg", blur_img);

}

void testManySigmas(const std::string &name) {
    // TODO возьмите ту же самую картинку но теперь в цикле проведите сглаживание для нескольких разных сигм
    // при этом результирующую картинку сохраняйте с указанием какая сигма использовалась:
    // для того чтобы в название файла добавить значение этой переменной -
    // воспользуйтесь функцией преобразующей числа в строчки - std::to_string(sigma)
    double sigma = 3;
    /*for(double sigma = 0.2; sigma < 1.6; sigma += 0.2){
    cv::Mat img = cv::imread("lesson06/data/" + name + ".jpg");
    rassert(!img.empty(), 23981920813);
    cv::Mat blur_img = blur(img.clone(), sigma);
    cv::imwrite("lesson06/resultsData/" + name +  "_s=" + std::to_string(sigma) +".jpg", blur_img);
    }*/
    cv::Mat img = cv::imread("lesson06/data/" + name + ".jpg");
    rassert(!img.empty(), 23981920813);
    cv::Mat blur_img = blur(img.clone(), sigma);
    cv::imwrite("lesson06/resultsData/" + name +  "_s=" + std::to_string(sigma) +".jpg", blur_img);
}

int main() {
    try {
        //testSomeBlur();
        for(int i = 1; i <= 4; ++i) {
            testManySigmas("line0"+ std::to_string(i));
            testManySigmas("line1" + std::to_string(i));
        }
        testManySigmas("line21_water_horizont");
        testManySigmas("multiline1_paper_on_table");
        testManySigmas("multiline2_paper_on_table");
        testManySigmas("valve");

        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}

