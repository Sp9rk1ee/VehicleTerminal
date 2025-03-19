#include "jiemian.h"
#include "ui_jiemian.h"

JieMian::JieMian(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JieMian)
{
    ui->setupUi(this);

    icm20608 = new ICM20608(this);
    connect(icm20608,SIGNAL(icm20608DataChanged()),this,SLOT(getICM20608Data()));//定时器到时会触发这个信号，把新的数据显示到标签上
}

JieMian::~JieMian()
{
    delete ui;
}
//没用到
bool JieMian::eventFilter(QObject *watch, QEvent *evn)
{
    static int press_x;  //鼠标按下时的位置
    static int press_y;
    static int relea_x;  //鼠标释放时的位置
    static int relea_y;

    QMouseEvent *event = static_cast<QMouseEvent *>(evn); //将之转换为鼠标事件

    if(event->type()==QEvent::MouseButtonPress)  //如果鼠标按下
    {
        press_x = event->globalX();
        press_y = event->globalY();
    }

    if(event->type()==QEvent::MouseButtonRelease)  //如果鼠标释放
    {
         relea_x = event->globalX();
         relea_y = event->globalY();
    }

    //判断滑动方向（右滑）
    if((relea_x - press_x)>20 && event->type()==QEvent::MouseButtonRelease && qAbs(relea_y-press_y)<50)
    {
        int current_page = ui->stackedWidget->currentIndex();
        if(current_page<=2)
        {
            ui->label->setPixmap(ui->stackedWidget->currentWidget()->grab());  //捕获当前界面并绘制到label上

            QPropertyAnimation *animation1 = new QPropertyAnimation(ui->label,"geometry");
            animation1->setDuration(1000);  //设置动画时间为1秒
            animation1->setStartValue(QRect(0,0,this->width(),this->height()));
            animation1->setEndValue(QRect(this->width()*2,0,this->width(),this->height()));

            ui->stackedWidget->setCurrentIndex(current_page+1);  //切换界面

            QPropertyAnimation *animation2 = new QPropertyAnimation(ui->stackedWidget->currentWidget(),"geometry");
            animation2->setDuration(1000);
            animation2->setStartValue(QRect(-this->width()*2,0,this->width(),this->height()));
            animation2->setEndValue(QRect(0,0,this->width(),this->height()));

            QParallelAnimationGroup *group = new QParallelAnimationGroup;  //动画容器
            group->addAnimation(animation1);
            group->addAnimation(animation2);
            group->start();
        }
    }

    //判断滑动方向（左滑）
    if((press_x - relea_x)>20 && event->type()==QEvent::MouseButtonRelease && qAbs(relea_y-press_y)<50)
    {
        int current_page = ui->stackedWidget->currentIndex();
        if(current_page>=0)
        {
            //ui->label->setPixmap(ui->stackedWidget->currentWidget()->grab());

            QPropertyAnimation *animation1 = new QPropertyAnimation(ui->label,"geometry");
            animation1->setDuration(1000);
            animation1->setStartValue(QRect(0,0,this->width(),this->height()));
            animation1->setEndValue(QRect(-this->width(),0,this->width(),this->height()));

            ui->stackedWidget->setCurrentIndex(current_page-1);

            QPropertyAnimation *animation2 = new QPropertyAnimation(ui->stackedWidget->currentWidget(),"geometry");
            animation2->setDuration(1000);
            animation2->setStartValue(QRect(this->width()*2,0,this->width(),this->height()));
            animation2->setEndValue(QRect(0,0,this->width(),this->height()));

            QParallelAnimationGroup *group = new QParallelAnimationGroup;
            group->addAnimation(animation1);
            group->addAnimation(animation2);
            group->start();
        }
    }


    //ui->label->clear();
    return QWidget::eventFilter(watch,evn);
}

//定时器到时更新
void JieMian::getICM20608Data()
{
    ui->label_gx->setText(icm20608->gxData());
    ui->label_gy->setText(icm20608->gyData());
    ui->label_gz->setText(icm20608->gzData());
    ui->label_ax->setText(icm20608->axData());
    ui->label_ay->setText(icm20608->ayData());
    ui->label_az->setText(icm20608->azData());
    ui->label_temp->setText(icm20608->tempData());
}
