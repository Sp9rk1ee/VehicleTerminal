#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QTime>
#include <QMouseEvent>
#include <QDebug>
#include "opencv2/opencv.hpp"//OpenCV文件包含
#include "opencv.hpp"
using namespace cv;          //OpenCV命名空间
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Camera; }
QT_END_NAMESPACE

class Camera : public QWidget
{
    Q_OBJECT

public:
    Camera(QWidget *parent = nullptr);
    ~Camera();

    void open_camera();
    void close_camera();

private:
    void timerEvent(QTimerEvent *e);//定时器事件
    void mousePressEvent(QMouseEvent *event);

signals:
    void close_camera_();
private:
    Ui::Camera *ui;
    VideoCapture cap;//摄像头
};
#endif // CAMERA_H
