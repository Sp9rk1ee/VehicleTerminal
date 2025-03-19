#include "life.h"
#include "ui_life.h"

// life.cpp 是一个界面管理类，主要负责实现与生活相关的功能界面，比如相册、钟表、天气等模块的显示与交互。

// life类的构造函数，函数头里这些东西看不懂可以看Widget.cpp里那边开头的讲解
// 主要是干了实例化一些相关的控件，然后绑定了一些信号和槽函数
Life::Life(QWidget *parent,QWidget *parent1) :
    QWidget(parent),
    ui(new Ui::Life)
{
    ui->setupUi(this); // 它会将 Qt Designer 设计的 .ui 文件转换为 C++ 代码，并应用到当前的 QWidget（或 QMainWindow、QDialog 等）对象上。
                       // 通俗的讲它把你在 Qt Designer 里设计的界面（比如按钮、标签、输入框等）放到当前的widget（this）里。

    //  相册label下的按键
    ui->pushButton_photo->setFixedSize(ui->widget_photo->size()); // 设置按钮大小
    ui->pushButton_photo->setFlat(true);  // 让按钮变成扁平化样子
    ui->pushButton_photo->raise(); // 让它置于最上层，不被其它控件遮挡

    life_ui = new QWidget(parent1); // 创建一个QWidget的实力，并指定其父窗口为parent1
    life_ui->setFixedSize(1024,600); // 设置大小
    life_ui->hide(); // 将其隐藏

    //  相册
    photoViem = new PhotoViem(life_ui); // 实例化一个PhotoViem对象
    photoViem->hide();          // 隐藏
    photoLabel = new QLabel(ui->widget_photo); // 实例化一个QLabel，设置父控件为widget_photo

    //  钟表
    date_biao = new Date_biao(ui->widget_meter);
    date_biao->move(ui->widget_meter->width()/2-this->height()/4,-15); // 设置它的坐标
    date_biao->resize(this->width()/3,this->height()*2/3);//ui->widget_meter->width(), ui->widget_meter->height() 设置大小
    date_biao->raise();  // 把它置于最上层，以免被遮挡

    //  天气
    weather = new Weather(life_ui);
    weather->hide();

    ui->widget_meter->raise();  //  最上层

    // 发出pixmap_data信号，lamda表达式会被触发，首先是对 pixm 进行缩放，使其适应 widget_meter（用于显示天气的控件）的大小。
    // 然后将缩放后的 pixm 设置到 label_watcher 上，用于显示天气图像。
    // 然后降低 label_watcher 的层级，确保它不会覆盖其他 UI 元素。
    connect(weather,&Weather::pixmap_data,[=](QPixmap pixm){ 
        pixm = pixm.scaled(ui->widget_meter->width(), ui->widget_meter->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_watcher->setPixmap(pixm);
        ui->label_watcher->lower();
    });
    connect(photoViem,&PhotoViem::at_pixmap,[=](QPixmap pix){ // 和上面类似
        photoLabel->setFixedSize(ui->widget_photo->size());
        photoLabel->setPixmap(pix.scaled(ui->widget_photo->width(), ui->widget_photo->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        photoLabel->lower();
        ui->pushButton_photo->move(0,0);
        ui->pushButton_photo->setFixedSize(pix.scaled(ui->widget_photo->width(), ui->widget_photo->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation).size());
        //qDebug()<<ui->pushButton_photo->size()<<ui->pushButton_photo->x()<<ui->pushButton_photo->y()<<ui->widget_photo->x();
    });
}

Life::~Life()
{
    delete ui;
}

void Life::weather_diaplay(bool aaa)
{
    if(wifi_judge_)//wifi_judge_  life类里的一个变量，应该是判断是否链接到wifi
    {
        if(aaa) //  显示 如果传进来的bool变量是true，显示下面这些，同时发送信号hide_show_life
        {
            weather->show();
            life_ui->show();
            emit hide_show_life();
        }
        else        // 否则，隐藏天气
        {
            weather->hide();
        }
    }
    else
        qDebug()<<"没用检测到网络信号！！！！";

}
// 对life成员中的wifi_judge_变量进行赋值，用于判断wifi是否可用
void Life::wifi_judge(bool wifiJudge)
{
    wifi_judge_ = wifiJudge;
}
//隐藏一些东西
void Life::hide_all()
{
    photoViem->hide__();
    weather->hide();
    life_ui->hide();
    weather_diaplay(false);
}
//槽函数，当pushButton_photo按钮被按下会触发，会显示一些东西，然后发送hide_show_life函数
void Life::on_pushButton_photo_clicked()
{
    //qDebug()<<ui->widget_photo->size()<<photoLabel->width()<<photoLabel->height()<<ui->pushButton_photo->width()<<ui->pushButton_photo->height();
    photoViem->show();
    life_ui->show();
    emit hide_show_life();
}
