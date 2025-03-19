#include "camera.h"
#include "ui_camera.h"

Camera::Camera(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Camera)
{
    ui->setupUi(this);

    //open_camera();
}

Camera::~Camera()
{
    delete ui;
}

void Camera::open_camera()
{
    // 打开摄像头
    cap.open(0);
    if(!cap.isOpened())
        qDebug()<<"摄像头打开失败";

    // 启动定时器事件
    startTimer(100);//100毫秒启动一次
}

void Camera::close_camera()
{
    cap.release();  // 关闭摄像头

}

void Camera::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e)

    // 采集数据
    Mat srcImage;
    if(cap.grab())           //判断有没有数据
    {
        cap.read(srcImage);  // 读取一帧数据
    }

    // 显示数据
    if(srcImage.data == nullptr) return;  // 等于空，返回
    // 把opencv里面的Mat格式数据(BGR)转为qt里面的QImage(RGB)
    cvtColor(srcImage,srcImage,COLOR_BGR2RGB);
    QImage image(srcImage.data,srcImage.cols,srcImage.rows,srcImage.step1(),QImage::Format_RGB888);
    QPixmap mmp = QPixmap::fromImage(image);
    ui->label->setPixmap(mmp);
}

void Camera::mousePressEvent(QMouseEvent *event)
{
     // 如果是鼠标左键按下
     if(event->button() == Qt::LeftButton)
     {
         close_camera();
         emit close_camera_();
     }
}
