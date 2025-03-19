#ifndef KEY_H
#define KEY_H

#include <QWidget>
#include <QKeyEvent>
//#include "ap3216c.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Key; }
QT_END_NAMESPACE

class Key : public QWidget
{
    Q_OBJECT

public:
    Key(QWidget *parent = nullptr);
    ~Key();

    void keyPressEvent_1(QKeyEvent *event);   // 按下
    void keyReleaseEvent_1(QKeyEvent *event); // 松开

private:
    // 重写按键按下的事件
    void keyPressEvent(QKeyEvent *event) override;   // 按下
    void keyReleaseEvent(QKeyEvent *event) override; // 松开

private slots:
    void getAp3216cData();       // 获取传感器数据

signals:
    void main_show();

private:
    Ui::Key *ui;
    //Ap3216c *ap3216c;
};
#endif // KEY_H
