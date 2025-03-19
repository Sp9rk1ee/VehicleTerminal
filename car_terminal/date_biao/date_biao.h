#ifndef DATE_BIAO_H
#define DATE_BIAO_H

#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QPixmap>

/*************表**************/

class Date_biao : public QWidget
{
    Q_OBJECT

public:
    Date_biao(QWidget *parent = nullptr);
    ~Date_biao();

    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    int h = 0, m = 0, s = 0;   //定义三个变量来存储时，分，秒
    int timer;   //存储计时器返回的序号
};
#endif // DATE_BIAO_H
