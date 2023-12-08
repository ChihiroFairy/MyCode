#include "mainwindow.h"
#include "serialport.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialPort serial;
    MainWindow w;
    w.show();
    return a.exec();
}
