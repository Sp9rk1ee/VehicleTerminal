#include "my_listwidget.h"

My_ListWidget::My_ListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setViewMode(QListView::ListMode);//设置列表控件的显示模式为 ListMode，即每个列表项以垂直列表的形式显示
    setFlow(QListView::TopToBottom);//设置列表项的排列方向为从上到下排列
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//设置垂直滚动条的滚动方式为“按像素滚动
    QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);//启用对滚动手势的支持

//    for(int i = 0; i < 1000; ++i)
//    {
//        addItem(new QListWidgetItem( QString::number(i)));
//    }
}

//用于处理鼠标滚轮事件，自动调用
void My_ListWidget::wheelEvent(QWheelEvent* event)
{
    int degress = event->angleDelta().ry() * 0.5;//返回一个 QPoint 类型的值，表示滚轮事件的增量
    if(event->orientation() == Qt::Vertical)//如果滚动方向是垂直方向
        verticalScrollBar()->setValue(verticalScrollBar()->value() - degress);//通过滚轮调整 QListWidget 的滚动条值
    event->accept();//表示事件已经被处理，防止该事件继续传递给其他控件
}
