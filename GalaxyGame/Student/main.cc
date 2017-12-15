//external
#include <QApplication>

//internal
#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace Student;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *start_window = new MainWindow();

    start_window->show();

    return a.exec();
}
