#include "widget.h"
#include <QApplication>
#include <QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pix(":/car_terminall/init.png"); 
    splsh.show(); 
    a.processEvents();

    Widget w; 
    w.show(); 

    splsh.finish(&w); 

    return a.exec();
}
