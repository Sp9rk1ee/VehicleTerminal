#include "musicplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MusicPlay w;
    w.show();
    return a.exec();
}
