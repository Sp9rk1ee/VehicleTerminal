#include "jiemian.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JieMian w;
    a.installEventFilter(&w);
    w.show();
    return a.exec();
}
