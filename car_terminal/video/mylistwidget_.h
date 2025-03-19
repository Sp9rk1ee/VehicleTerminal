#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QScroller>
#include <QWheelEvent>
#include <QScrollBar>

class MyListWidget_ : public QListWidget
{
    Q_OBJECT
public:
    MyListWidget_(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event);
};

#endif // MYLISTWIDGET_H
