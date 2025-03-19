#ifndef TOOL_H
#define TOOL_H

#include <QWidget>
#include <QTimer>
#include <QTextEdit>
#include <QLabel>
#include <QDebug>
#include <compass/compass.h>
#include <key/ap3216c.h>
#include <key/icm20608.h>
#include <key/led.h>
#include <folder/folder.h>
#include <wifi/wifi.h>
#include <set_arm/set_arm.h>
//#include <camera/camera.h>


// 主要定义了一个Tool类，以及它的一些槽函数，信号什么的

namespace Ui {
class Tool;
}

class Tool : public QWidget
{
    Q_OBJECT

public:
    explicit Tool(QWidget *parent = nullptr,QWidget *parent1 = nullptr);
    ~Tool();

    void useName(bool);
    void hide_all();

private slots:
    void on_pushButton_folder_clicked();

    void on_pushButton_light_clicked();

    void on_pushButton_backcar_clicked();

    void on_pushButton_wifi_clicked();

    void on_pushButton_instructions_clicked();

    void on_pushButton_set_clicked();

signals:
    void wifi_judge(bool);
    void hide_show_tool();
    void bizi_path(QString);
    void use_name(bool);

private:
    Ui::Tool *ui;
    Folder *folder;
    //Camera *camera;
    QWidget *tool_ui;
    QTextEdit *textEdit_instructions;
    Compass *compss;
    QLabel *compss_label;
    Set_arm *set_arm;
#ifdef Q_OS_LINUX
    Led *led;
    ICM20608 *icm20608;
    Ap3216c *ap3216c;
    Wifi *wifi;
    bool led_state;
    int led_big;
#endif
    QString instructions_QString = "\n#####使用说明#####\n\n"
                                   "#欢迎大家使用，借鉴。本程序借鉴了很多网上大佬的开源资料，勿喷。\n"
                                   "\n#程序是按照正点原子IMX6U阿尔法开发板来编写的，其中几个模块功能需要"
                                   "板载硬件才可以实现。\n"
                                   "\n#WiFi功能模块，是需要板子购买时赠送的wifiUSB模块的，wifi程序是直接"
                                   "调用板载驱动，进行连接wifi和查看周围wifi。\n"
                                   "\n#地图功能模块是（天地图）连接api，获取地图、经纬度数据，地名搜索经纬"
                                   "度不太准确，导致地图图片不太准确，搜索地标性建筑还是可以的，建议"
                                   "把api改为高德或者百度的应该会好一点。\n"
                                   "\n#指南针是根据板载硬件ICM20608六轴传感器其中的x、y轴来计算的，指南"
                                   "针不准（作者较为废物，建议修改一下）。\n"
                                   "\n#倒车影像功能模块，使用OpenCV来实现的。\n"
                                   "\n#天气功能模块,连接api获取天气，作者这个api比较捞（次数少），建议更"
                                   "换，钟表后面显示当前天气状况，天气应用有两个界面，界面1，当天的天气情"
                                   "况，单机屏幕切换界面2，未来5天的天气情况。\n"
                                   "\n#键盘输入中文功能模块，是应用开源大佬\n"
                                   "https://github.com/justdoit-mqr/softkeyboard。\n"
                                   "\n#浏览器功能和收音机功能，暂时还没有开发，各位大佬可以自行研究。\n\n"
                                   "\n#####建议#####\n\n"
                                   "#有一些默认的路径可以自己根据自己电脑进行更改，如：默认连接的wifi，文件"
                                   "夹功能模块下windows下的路径等。\n"
                                   "\n#键盘功能开启了两次，可以自己优化为一次。\n"
                                   "\n#语音识别功能模块（voice）是根据百度语音识别来实现的，因为有时不太"
                                   "准确，本程序没有使用，可以自行添加该功能。也可以购买模块编写驱动来实现语音功能。\n";
};

#endif // TOOL_H
