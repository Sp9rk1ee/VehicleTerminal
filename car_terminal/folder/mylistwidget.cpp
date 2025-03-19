#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setViewMode(QListView::ListMode);//设置 QListView 的显示模式,QListView::ListMode: 表示以列表模式显示项，项目会按垂直方向排列，每项占一行
    setFlow(QListView::TopToBottom);// 设置列表排列的流向，QListView::TopToBottom: 这表示项目将从上往下排列。
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//设置垂直滚动方式，ScrollPerPixel: 表示滚动条滚动时，按像素进行滚动
    QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);// 该方法允许启用触摸手势支持，允许用户使用鼠标左键进行拖动操作来滚动列表

    for(int i = 0; i < 1000; ++i)
    {
        //在每次循环中，都会向 QListWidget 添加一个新的项目，每个项目显示一个数字字符串，从 "0" 到 "999"。
        addItem(new QListWidgetItem( QString::number(i)));
    }
}
//这段代码是重载了 QListWidget 类的 wheelEvent 方法，用于处理鼠标滚轮事件。
//它的作用是自定义鼠标滚轮滚动时的行为，特别是用来控制 QListWidget 中的滚动条。
void MyListWidget::wheelEvent(QWheelEvent* event)//这个参数是传递给wheelEvent方法的事件对象,它包含了有关滚轮事件的所有信息，例如滚动的角度、方向等
{   
    //event->angleDelta().ry() 返回的值是垂直方向的滚动增量。
    int degress = event->angleDelta().ry() * 0.5;//这里的 degress 实际上是将滚动增量进行缩放。通过乘以 0.5，表示每次滚动的步长只有原来的一半
    if(event->orientation() == Qt::Vertical)//判断滚轮事件的方向。如果是垂直滚动
        verticalScrollBar()->setValue(verticalScrollBar()->value() - degress);//通过 setValue() 方法设置新的滚动条位置。degress 是滚动的增量
    event->accept();//这行代码告诉事件系统，事件已经被处理过了，事件不需要进一步传播
}
