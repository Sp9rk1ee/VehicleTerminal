#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
//#include <voice/voice.h> //  语音识别
#include "key/key.h"
#include "slidepage/slidepage.h"
#include "life.h"
#include "use.h"
#include "tool.h"

QT_BEGIN_NAMESPACE
// 这是在 Ui 命名空间中声明了一个类 Widget 的前向声明（forward declaration）。
// 前向声明是告诉编译器，Widget 类在某个地方定义了，但暂时不需要详细定义它。这是为了让代码可以在 Widget 类的定义之前使用它的指针类型。
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget // 定义一个Widget类，继承自QWidget
{
    Q_OBJECT // Q_OBJECT 宏允许你在类中使用 Qt 的 信号和槽机制

public:
    Widget(QWidget *parent = nullptr); // 构造函数，传入的指针为空表示没有父控件
    ~Widget(); // 析构函数

private slots: // 槽函数
    // 重写按键按下的事件
    void keyPressEvent(QKeyEvent *event) override;   // 按下，重写QWidget自带的一个槽函数，当键盘任意一个键被按下时会自动触发
    void keyReleaseEvent(QKeyEvent *event) override; // 松开，同上
    void on_pushButton_life_clicked(); // 当生活按键被按下
    void on_pushButton_use_clicked(); // 当应用按键被按下
    void on_pushButton_tool_clicked(); // 当工具按键被按下
    void wallpaper_change(QString); // 改变当前显示的壁纸
    void use_name(bool);
    void exit_all(); // 可能是退出应用程序
    void hide_widget(); // 可能是隐藏某个控件或窗口



private:
    Ui::Widget *ui; // 定义一个指向Widget类的指针ui
    QLabel *setting; // 定义一个指向QLabel类的指针，下面都是同理
    SlidePage *slidePage; // 这个应该是与页面滑动相关
    Life *life; // 生活
    Use *use; // 应用
    Tool *tool; // 工具
    Key *key; // 应该是和按键处理相关
};
#endif // WIDGET_H
