#ifndef MYMAP_H
#define MYMAP_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include "longitudelatitude.h"  // 天地图
#include "map.h"                // 天地图
#include "softkeyboard/softkeyboard.h"

/*************地图**************/

QT_BEGIN_NAMESPACE
namespace Ui { class MyMap; }
QT_END_NAMESPACE

class MyMap : public QWidget
{
    Q_OBJECT

public:
    MyMap(QWidget *parent = nullptr);
    ~MyMap();

public slots:
    void get_map(double longitude,double latitude);

private slots:
    void map_image_show(QImage *map_image);

    void on_pushButton_seek_clicked();

    void mousePressEvent(QMouseEvent *event);  // 鼠标单机事件

    void mouseReleaseEvent(QMouseEvent *event);// 鼠标松开事件

    void mouseMoveEvent(QMouseEvent *event);   // 鼠标移动事件

    void on_pushButton_magnify_clicked();

    void on_pushButton_reduce_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::MyMap *ui;
    LongitudeLatitude *longitudeLatitude;
    Map *map;
    SoftKeyboard *softKeyboard;
    QLabel *map_show;
    int m_zoom;
    double m_longitude;
    double m_latitude;
    QPoint lastMousePos;
    bool isMousePressed;
    int mouse_number;
};
#endif // MYMAP_H
