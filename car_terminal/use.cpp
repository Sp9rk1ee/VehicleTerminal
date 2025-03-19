#include "use.h"
#include "ui_use.h"

// 和tool.cpp类似，这个 use.cpp 文件定义了 Use 类的实现，主要作用是管理用户界面的不同功能模块，
// 比如浏览器、地图、音乐播放、视频播放、天气信息和收音机等。

// 很多一样的部分就不注释了，具体可以看widget.cpp那边比较详细
Use::Use(QWidget *parent,QWidget *parent1) :
    QWidget(parent),
    ui(new Ui::Use)
{
    ui->setupUi(this);

    use_ui = new QWidget(parent1);
    use_ui->setFixedSize(1024,600);
    use_ui->hide();

    mymap = new MyMap(use_ui);
    mymap->hide();
    musicPlay = new MusicPlay(use_ui);
    musicPlay->setAttribute(Qt::WA_StyledBackground); //  允许 musicPlay 使用样式表的 background 属性。
    musicPlay->hide();
    video = new Video(use_ui);
    video->hide();
}

Use::~Use()
{
    delete ui;
}

void Use::useName(bool use_name)
{
    if(use_name)  //  显示
    {
        ui->label_browser->show(); // 在use.ui文件里面定义
        ui->label_map->show();
        ui->label_music->show();
        ui->label_raido->show();
        ui->label_video->show();
        ui->label_weather->show();
    }
    else
    {
        ui->label_browser->hide();
        ui->label_map->hide();
        ui->label_music->hide();
        ui->label_raido->hide();
        ui->label_video->hide();
        ui->label_weather->hide();
    }
}

void Use::wifi_judge(bool wifiJudge)
{
    wifi_judge_ = wifiJudge;
}

void Use::hide_all()
{
    mymap->hide();
    musicPlay->hide();
    video->hide();
    use_ui->hide();
    //use_ui->setStyleSheet("background-color: rgb(0, 0, 0);");
}

void Use::on_pushButton_video_clicked()
{
    use_ui->show();
    video->show();
    emit hide_show_use();
}

void Use::on_pushButton_music_clicked()
{
    use_ui->show();
    //use_ui->setStyleSheet("background-color: rgb(81, 81, 81);");
    musicPlay->show();
    emit hide_show_use();
}

void Use::on_pushButton_browser_clicked() //浏览器
{
    qDebug()<<"\n暂无“浏览器”功能，作者会努力的！！！";
}

void Use::on_pushButton_weather_clicked()
{
    if(wifi_judge_)
        emit weather_show();
    else
        qDebug()<<"没用检测到网络信号！！！";
}

void Use::on_pushButton_map_clicked()
{
    if(wifi_judge_)
    {
        use_ui->show();
        mymap->show();
        emit hide_show_use();
    }
    else
        qDebug()<<"没用检测到网络信号！！！";
}

void Use::on_pushButton_radio_clicked()
{
    qDebug()<<"\n暂无“收音机”功能，作者会努力的！！！";
}
