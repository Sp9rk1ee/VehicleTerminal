#include "compass.h"
#include "ui_compass.h"

Compass::Compass(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::Compass)
    ,_direction(0.0)  // 初始化_direction为0，_campass_scale为4/5
    ,_campass_scale(4.0 / 5.0)
{
    ui->setupUi(this);
}

Compass::~Compass()
{
    delete ui;
}

// 对传进来的指南针方向进行归一化,并对图像进行重新绘画
void Compass::set_direction(const float direction) {
    _direction = float(int(direction) % 360) + float(direction - float(int(direction)));
    //qDebug()<<QString::number(_direction) + QApplication::translate("Compass", "\302\260", nullptr);
    update();// update是qt自带的，调用update会自动调用paintEvent函数
}

// 设置指南针的缩放比例
void Compass::set_campass_scale(const float scale) {
    _campass_scale = scale;
}

void Compass::set_campass_scale(const quint32 widget_scale, const quint32 campass_scale) {
    _campass_scale = float(campass_scale) / float(widget_scale);
}

// 绘制指南针
void Compass::paintEvent(QPaintEvent *event) {
    int side = qMin(this->width() * _campass_scale, this->height() * _campass_scale);

    QColor calibration_color(0, 127, 127, 191);

    static const QString direction_name[] = {
        QString("N"), QString("NE"),
        QString("E"), QString("ES"),
        QString("S"), QString("WS"),
        QString("W"), QString("NW")
    };

    static const QPoint red_left[] = {
        QPoint(0, 0),
        QPoint(-7, 0),
        QPoint(0, -70)
    };

    static const QPoint red_right[] = {
        QPoint(7, 0),
        QPoint(0, 0),
        QPoint(0, -70)
    };

    static const QPoint white_left[] = {
        QPoint(0, 0),
        QPoint(-7, 0),
        QPoint(0, 70)
    };

    static const QPoint white_right[] = {
        QPoint(7, 0),
        QPoint(0, 0),
        QPoint(0, 70)
    };


    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(this->width() / 2, this->height() * _campass_scale / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(calibration_color);
    painter.setPen(Qt::black); //  外圈颜色.推荐calibration_color

    for (int i = 0; i < 18; ++i) {
        painter.save();
        painter.setFont(QFont("Times", 10));
        painter.rotate(-90.0);
        painter.rotate(20.0 * i);
        painter.translate(95, 0);
        painter.rotate(90.0);

        painter.drawText(QRect(-19, -7, 38, 14), Qt::AlignCenter, QString::number(i * 20));

        painter.restore();
    }

    painter.save();
    painter.rotate(-90.0);
    for (int i = 0; i < 18; ++i) {
        painter.drawLine(78, 0, 88, 0);
        painter.rotate(20.0);
    }
    painter.restore();

    painter.save();
    for (int i = 0; i < 36; ++i) {
        if ((i % 10) != 0)
            painter.drawLine(82, 0, 88, 0);
        painter.rotate(20.0);
    }
    painter.restore();

    painter.save();
    for (int i = 0; i < 180; ++i) {
        if ((i % 5) != 0)
            painter.drawLine(84, 0, 88, 0);
        painter.rotate(2.0);
    }
    painter.restore();

    painter.save();
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::red);
    int pix = 8;
    for (int i = 0; i < 8; ++i) {
        painter.drawArc(-70, -70, 140, 140, (45 * i + pix) * 16, (45 - 2*pix) * 16);
    }

    painter.restore();


    for (int i = 0; i < 8; ++i) {
        painter.save();

        if (i == 0) {
            painter.setPen(Qt::red);
        } else {
            painter.setPen(Qt::blue);
        }
        painter.setBrush(Qt::white);

        if (i % 2 == 0) {
            painter.setFont(QFont("Times", 12, QFont::Bold));
        } else {
            painter.setFont(QFont("Times", 8));
        }

        painter.rotate(-90.0);
        painter.rotate(45.0 * i);
        painter.translate(70, 0);
        painter.rotate(90.0);

        painter.drawText(QRect(-19, -7, 38, 14), Qt::AlignCenter, direction_name[i]);

        painter.restore();
    }

    //  针
    painter.save();
    painter.rotate(_direction);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(Qt::darkRed));
    painter.drawConvexPolygon(red_left, 3);
    painter.setBrush(QColor(Qt::red));
    painter.drawConvexPolygon(red_right, 3);
    painter.setBrush(QColor(Qt::lightGray));
    painter.drawConvexPolygon(white_left, 3);
    painter.setBrush(QColor(Qt::white));
    painter.drawConvexPolygon(white_right, 3);
    painter.restore();
}
