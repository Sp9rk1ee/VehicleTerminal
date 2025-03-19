#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QScroller>
#include <QWheelEvent>
#include <QScrollBar>

class My_ListWidget : public QListWidget
{
    Q_OBJECT
public:
    My_ListWidget(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event);
};

#endif // MYLISTWIDGET_H
