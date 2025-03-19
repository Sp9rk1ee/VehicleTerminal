#include "folder.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Folder w;
    w.show();
    return a.exec();
}
