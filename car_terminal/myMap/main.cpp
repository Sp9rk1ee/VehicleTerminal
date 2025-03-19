#include "mymap.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMap w;
    w.show();
    return a.exec();
}
