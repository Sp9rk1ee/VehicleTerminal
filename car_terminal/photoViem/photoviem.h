#ifndef PHOTOVIEM_H
#define PHOTOVIEM_H

#include <QWidget>
#include <QPushButton>
#include <QFile>
#include <QDir>
#include <QFileInfoList>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>
#include "pitherbig.h"  
#include "folder/mylistwidget.h"

/*************相册**************/

QT_BEGIN_NAMESPACE
namespace Ui { class PhotoViem; }
QT_END_NAMESPACE

class PhotoViem : public QWidget
{
    Q_OBJECT

public:
    PhotoViem(QWidget *parent = nullptr);
    ~PhotoViem();

    void hide__();
private slots:
    void on_pushButton_left0(bool);
    void on_pushButton_right0(bool);
    void show_widget();
    void on_listWidget_photo_itemClicked(QListWidgetItem *item);


private:
    void scanPicture();
    void mousePressEvent(QMouseEvent *event);

signals:
    void at_pixmap(QPixmap);
public:
    QVector<QPixmap> pixmapData;

private:
    Ui::PhotoViem *ui;
    MyListWidget *widget_photo;
    QPushButton *pushButton_left;
    QPushButton *pushButton_right;
    QTimer *timerConversion;
    QTimer *timerdoubleClick;
    PitherBig *pitherBig;
    int item_number;
};
#endif // PHOTOVIEM_H
