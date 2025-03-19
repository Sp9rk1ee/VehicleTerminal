#include "set_arm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Set_arm w;
    w.show();
    return a.exec();
}
