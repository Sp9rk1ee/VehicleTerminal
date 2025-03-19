#ifndef COMPASS_H
#define COMPASS_H

#include <QFrame>
#include <QEvent>
#include <QPainter>
#include <QRect>
#include <QDebug>

/*************指南针**************/

QT_BEGIN_NAMESPACE
namespace Ui { class Compass; }
QT_END_NAMESPACE

class Compass : public QFrame
{
    Q_OBJECT

public:
    Compass(QWidget *parent = nullptr);
    ~Compass();

public slots:
    void set_direction(const float direction);
    void set_campass_scale(const float scale);  // 设置指南针在控件中的比例
    void set_campass_scale(const quint32 widget_scale, const quint32 campass_scale);  // 设置指南针在控件中的比例

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Compass *ui;

    float _direction;  //  方向
    float _campass_scale;
};
#endif // COMPASS_H
