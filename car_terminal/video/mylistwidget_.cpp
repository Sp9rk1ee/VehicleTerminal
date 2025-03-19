#include "mylistwidget_.h"

MyListWidget_::MyListWidget_(QWidget *parent)
    : QListWidget(parent)
{
    setViewMode(QListView::ListMode);//设置视图模式为 "ListMode"（列表模式）。这意味着列表项会按顺序排列为一列（垂直方向）
    setFlow(QListView::TopToBottom);//设置控件中的列表项流动的方向为从上到下
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//设置垂直滚动模式为“按像素滚动”
    QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);//启用了手势支持，使得 MyListWidget_ 能够响应鼠标左键点击的滚动手势

//    for(int i = 0; i < 1000; ++i)
//    {
//        addItem(new QListWidgetItem( QString::number(i)));
//    }
}

//鼠标滚轮滚动时自动调用
void MyListWidget_::wheelEvent(QWheelEvent* event)
{
    //通过计算滚动量来更新滚动条的位置
    int degress = event->angleDelta().ry() * 0.5;
    if(event->orientation() == Qt::Vertical)
        verticalScrollBar()->setValue(verticalScrollBar()->value() - degress);
    event->accept();//表示当前事件已经被处理，不需要进一步传递
}
