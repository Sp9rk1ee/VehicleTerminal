#include "photoviem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PhotoViem w;
    w.show();
    return a.exec();
}
