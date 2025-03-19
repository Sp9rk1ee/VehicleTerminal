#ifndef LIFE_H
#define LIFE_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <weather/weather.h>
#include <photoViem/photoviem.h>
#include <date_biao/date_biao.h>

namespace Ui {
class Life;
}

class Life : public QWidget
{
    Q_OBJECT  // Q_OBJECT 宏允许你在类中使用 Qt 的 信号和槽机制

public:
    explicit Life(QWidget *parent = nullptr,QWidget *parent1 = nullptr); // 构造函数，别管explicit
    ~Life();  // 析构函数

    void weather_diaplay(bool);  //  显示天气界面
    void wifi_judge(bool);       //  获取wifi是否可以使用
    void hide_all();  // 隐藏一些东西

private slots:
    void on_pushButton_photo_clicked();  // 槽函数，当pushButton_photo被按下时触发

signals:
    void hide_show_life();  // 信号

private:  
    Ui::Life *ui;
    QLabel *photoLabel;
    QTimer *photoTimer;
    QWidget *life_ui;
    Date_biao *date_biao;
    PhotoViem *photoViem;
    Weather *weather;
    bool wifi_judge_;
};

#endif // LIFE_H
