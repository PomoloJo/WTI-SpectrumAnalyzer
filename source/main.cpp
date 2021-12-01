#include "./include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // global font
    QFont global_font("Arial", 10);
    a.setFont(global_font);







    MainWindow w;
    w.show();

    return a.exec();
}
