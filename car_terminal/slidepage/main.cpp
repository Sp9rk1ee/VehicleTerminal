#include "slidepage.h"

#include <QApplication>

// 这个main只会在单独测试该模块的时候才会用到
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SlidePage w;
    w.show();
    return a.exec();
}
