#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.showDirectory();
    w.getParser("");
    //w.showTable();

    return a.exec();
}
