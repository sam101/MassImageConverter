#include <QtGui/QApplication>
#include "MainWindow.h"
#include <Converter.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList list;
    list << "image.JPG";

    Converter c;
    c.start(list,QSize(1000,1000));

    return a.exec();
}
