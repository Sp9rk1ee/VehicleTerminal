#include "voice.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Voice w;
    w.show();
    return a.exec();
}
