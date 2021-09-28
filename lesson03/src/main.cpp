#include <iostream>
#include <filesystem> // это нам понадобится чтобы создать папку для результатов
#include <libutils/rasserts.h>

#include "helper_functions.h"

#include <opencv2/highgui.hpp> // подключили часть библиотеки OpenCV, теперь мы можем читать и сохранять картинки

void task1() {
    cv::Mat imgUnicorn = cv::imread("lesson03/data/unicorn.png");  // загружаем картинку с единорогом
    rassert(!imgUnicorn.empty(), 3428374817241); // проверяем что картинка загрузилась (что она не пустая)

    // TODO выведите в консоль разрешение картинки (ширина x высота)
    int width = 0; // как в ООП - у картинки есть поля доступные через точку, они называются cols и rows - попробуйте их
    int height = 0;

    width = imgUnicorn.cols;
    height = imgUnicorn.rows;
    std::cout << "Unicorn image loaded: " << width << "x" << height << std::endl;

    // создаем папку в которую будем сохранять результаты - lesson03/resultsData/
    std::string resultsDir = "lesson03/resultsData/";
    if (!std::filesystem::exists(resultsDir)) { // если папка еще не создана
        std::filesystem::create_directory(resultsDir); // то создаем ее
    }

    cv::Mat blueUnicorn = makeAllBlackPixelsBlue(imgUnicorn.clone()); // TODO реализуйте функцию которая каждый пиксель картинки который близок к белому - делает синим
    std::string filename = resultsDir + "01_blue_unicorn.jpg"; // удобно в начале файла писать число, чтобы файлы были в том порядке в котором мы их создали
    cv::imwrite(filename, blueUnicorn);


    // TODO сохраните резльутат в ту же папку, но файл назовите "02_inv_unicorn.jpg"
    cv::Mat invertUnicorn = invertImageColors(imgUnicorn.clone());
    std::string filename1 = resultsDir + "02_inv_unicorn.jpg";
    cv::imwrite(filename1, invertUnicorn);


    cv::Mat castle = cv::imread("lesson03/data/castle.png"); // TODO считайте с диска картинку с замком - castle.png
    cv::Mat unicornInCastle = addBackgroundInsteadOfBlackPixels(imgUnicorn.clone(), castle); // TODO реализуйте функцию которая все черные пиксели картинки-объекта заменяет на пиксели с картинки-фона
    // TODO сохраните результат в ту же папку, назовите "03_unicorn_castle.jpg"
    std::string filename2 = resultsDir + "03_unicorn_castle.jpg";
    cv::imwrite(filename2, unicornInCastle);

    cv::Mat largeCastle = cv::imread("lesson03/data/castle_large.jpg"); // TODO считайте с диска картинку с большим замком - castle_large.jpg
    std::cout << "Large Castle image loaded: " << largeCastle.cols << "x" << largeCastle.rows << std::endl;

    cv::Mat unicornInLargeCastle = addBackgroundInsteadOfBlackPixelsLargeBackground(imgUnicorn.clone(), largeCastle.clone());
    // TODO реализуйте функцию так, чтобы нарисовался объект ровно по центру на данном фоне, при этом черные пиксели объекта не должны быть нарисованы
    // TODO сохраните результат - "04_unicorn_large_castle.jpg"
    std::string filename3 = resultsDir + "04_unicorn_large_castle.jpg";
    cv::imwrite(filename3, unicornInLargeCastle);

    cv::Mat randomUnicornsInLargeCastle = addUnicornsOnLargeBackground(imgUnicorn.clone(), largeCastle.clone());
    std::string filename4 = resultsDir + "05_unicorns_otake.jpg";
    cv::imwrite(filename4, randomUnicornsInLargeCastle);

    // TODO сделайте то же самое, но теперь пусть единорог рисуется N раз (случайно выбранная переменная от 0 до 100)


    // TODO растяните картинку единорога так, чтобы она заполнила полностью большую картинку с замком "06_unicorn_upscale.jpg"
}

void task2() {
    cv::Mat imgUnicorn = cv::imread("lesson03/data/unicorn.png");
    rassert(!imgUnicorn.empty(), 3428374817241);

    // cv::waitKey - функция некоторое время ждет не будет ли нажата кнопка клавиатуры, если да - то возвращает ее код
    int updateDelay = 10; // указываем сколько времени ждать нажатия кнопки клавиатуры - в миллисекундах
    while (cv::waitKey(updateDelay) != 32) {
        // поэтому если мы выполняемся до тех пор пока эта функция не вернет код 32 (а это код кнопки "пробел"), то достаточно будет нажать на пробел чтобы закончить работу программы

        // кроме сохранения картинок на диск (что часто гораздо удобнее конечно, т.к. между ними легко переключаться)
        // иногда удобно рисовать картинку в окне:
        //cv::imshow("lesson03 window", imgUnicorn);
        // TODO сделайте функцию которая будет все черные пиксели (фон) заменять на случайный цвет (аккуратно, будет хаотично и ярко мигать, не делайте если вам это противопоказано)
        cv::imshow("colorUnicorn", makeAllBlackPixelsToRandomColor(imgUnicorn.clone()));

    }
}

struct MyVideoContent {
    cv::Mat frame;
    std::vector<int> allXCoords;
    std::vector<int> allYCoords;
    int lastClickX = 1;
    int lastClickY = 1;
    bool inverting = false;
};

void onMouseClick(int event, int x, int y, int flags, void *pointerToMyVideoContent) {
    MyVideoContent &content = *((MyVideoContent*) pointerToMyVideoContent);
    // не обращайте внимание на предыдущую строку, главное что важно заметить:
    // content.frame - доступ к тому кадру что был только что отображен на экране
    // content.lastClickX - переменная которая вам тоже наверняка пригодится
    // вы можете добавить своих переменных в структурку выше (считайте что это описание объекта из ООП, т.к. почти полноценный класс)


    if (event == cv::EVENT_LBUTTONDOWN) { // если нажата левая кнопка мыши
        std::cout << "Left click at x=" << x << ", y=" << y << std::endl;
        content.allXCoords.push_back(x);
        content.allYCoords.push_back(y);
        content.lastClickX = x;
        content.lastClickY = y;
    }

    if (event == cv::EVENT_RBUTTONDOWN) { // если нажата левая кнопка мыши
        std::cout << "Right click at x=" << x << ", y=" << y << std::endl;
        content.inverting = !content.inverting;
    }
}

void task3() {
    // давайте теперь вместо картинок подключим видеопоток с веб камеры:
    cv::VideoCapture video(0);

    //cv::VideoCapture video("lesson03/data/debats.mp4");

    rassert(video.isOpened(), 3423948392481); // проверяем что видео получилось открыть
    std::cout << "video is opened" << std::endl;
    MyVideoContent content; // здесь мы будем хранить всякие полезности - например последний видео кадр, координаты последнего клика и т.п.
    // content.frame - доступ к тому кадру что был только что отображен на экране
    // content.lastClickX - переменная которая вам тоже наверняка пригодится
    // вы можете добавить своих переменных в структурку выше (считайте что это описание объекта из ООП, т.к. почти полноценный класс)
    // просто перейдите к ее объявлению - удерживая Ctrl сделайте клик левой кнопкой мыши по MyVideoContent - и вас телепортирует к ее определению

    while (video.isOpened()) { // пока видео не закрылось - бежим по нему
        bool isSuccess = video.read(content.frame); // считываем из видео очередной кадр
        rassert(isSuccess, 348792347819); // проверяем что считывание прошло успешно
        rassert(!content.frame.empty(), 3452314124643); // проверяем что кадр не пустой
        //cv::imshow("video", content.frame);
         // покаызваем очередной кадр в окошке
        cv::setMouseCallback("video", onMouseClick, &content);
        int key = cv::waitKey(10);
        if(key == 32 || key == 27) break;

        if(content.inverting == false){
        cv::imshow("video",
                   makeAllClickedPixelsToRed(content.frame.clone(), content.allXCoords, content.allYCoords));}
        else{
            cv::imshow("video",
                       invertImageColors(makeAllClickedPixelsToRed(content.frame.clone(), content.allXCoords, content.allYCoords)));
        }

        }
}

void task4() {
    // TODO на базе кода из task3 (скопируйте просто его сюда) сделайте следующее:
    // TODO попробуйте сделать так чтобы цвет не обязательно совпадал абсолютно для прозрачности (чтобы все пиксели похожие на тот что был кликнут - стали прозрачными, а не только идеально совпадающие)

    cv::VideoCapture video(0);

    rassert(video.isOpened(), 3423948392481); // проверяем что видео получилось открыть
    std::cout << "video is opened" << std::endl;
    MyVideoContent content;

    while (video.isOpened()) { // пока видео не закрылось - бежим по нему
        bool isSuccess = video.read(content.frame); // считываем из видео очередной кадр
        rassert(isSuccess, 348792347819); // проверяем что считывание прошло успешно
        rassert(!content.frame.empty(), 3452314124643); // проверяем что кадр не пустой


        cv::setMouseCallback("video", onMouseClick, &content);
        int key = cv::waitKey(10);
        if(key == 32 || key == 27) break;


        //cv::Mat frameWithBG = makeLargeCastleInsteadClickedColor(content.frame.clone(), content.lastClickX, content.lastClickY);
        cv::Mat largeCastle = cv::imread("lesson03/data/castle_large.jpg");
        cv::imshow("video",
                   makeLargeCastleInsteadClickedColor(content.frame.clone(), content.lastClickX, content.lastClickY, largeCastle));


    }
    // TODO подумайте, а как бы отмаскировать фон целиком несмотря на то что он разноцветный?
    // а как бы вы справились с тем чтобы из фотографии с единорогом и фоном удалить фон зная как выглядит фон?
    // а может сделать тот же трюк с вебкой - выйти из вебки в момент запуска программы, и первый кадр использовать как кадр-эталон с фоном который надо удалять (делать прозрачным)
}

int main() {
    try {
        //task1();
       //task2();
        //task3();
       task4();
        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}
