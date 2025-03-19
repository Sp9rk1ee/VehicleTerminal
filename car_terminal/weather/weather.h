#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <QTimer>
#include <QDate>
#include <QMouseEvent>
#include "wforecast.h"
#include "softkeyboard/softkeyboard.h"
#include "../slidepage/slidepage.h"
#include "folder/mylistwidget.h"

/*************天气**************/

QT_BEGIN_NAMESPACE
namespace Ui { class Weather; }
QT_END_NAMESPACE

class Weather : public QWidget
{
    Q_OBJECT

public:
    Weather(QWidget *parent = nullptr);
    ~Weather();

private:
    void resizeEvent(QResizeEvent *event);  /* 重设大小 */

private slots:
    void on_pushButton_seek_clicked();
    void data_Updata();                     /* 显示更新 */
    void get_weather();
    void mousePressEvent(QMouseEvent *event);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void pixmap_data(QPixmap);
private:
    Ui::Weather *ui;
    SoftKeyboard *softKeyboard;
    SlidePage *mySlidePage;      /* 滑动页面管理对象 */
    QTimer *get_weather_timer;   /* 获取1000后才可以显示 */
    WForecast *weatherForecast;  /* 天气类 */
    bool data_up_judge;          /* 数据是否成功 */
};
#endif // WEATHER_H
