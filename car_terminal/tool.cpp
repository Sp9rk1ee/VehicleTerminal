#include "tool.h"
#include "ui_tool.h"

#include <math.h>


// tool.cpp 主要是一个 工具界面 (Tool 类)，它整合了多个子模块，如指南针 (Compass)、文件夹 (Folder)、WiFi (Wifi)、
// 传感器 (ICM20608, Ap3216c)、LED 灯 (Led)，以及系统设置 (Set_arm)。它的主要作用是 提供一个可视化界面，管理这些功能的显示和交互。

// 很多一样的不重复注释，具体可以看widget.cpp的注释，那边比较详细
Tool::Tool(QWidget *parent,QWidget *parent1) :
    QWidget(parent),
    ui(new Ui::Tool)
{
    ui->setupUi(this);

    tool_ui = new QWidget(parent1);
    tool_ui->setFixedSize(1024,600);
    tool_ui->hide();
    //  使用介绍
    textEdit_instructions = new QTextEdit(tool_ui);
    textEdit_instructions->setReadOnly(true);  //  只读
    textEdit_instructions->setStyleSheet("font: 13pt \"宋体\";");
    textEdit_instructions->resize(tool_ui->size());
    textEdit_instructions->append(instructions_QString); // 向 QTextEdit 控件追加一行文本。
    textEdit_instructions->hide();
    //  指南针
    compss = new Compass(ui->widget_compass);
    compss_label = new QLabel(this);
    compss_label->resize(140,40);
    compss_label->move(this->width()*2/3+6,this->height()*7/8); // 设置坐标
    compss_label->setAlignment(Qt::AlignCenter); // 设置 compss_label（QLabel 对象）的文本对齐方式，使其文本居中显示
    compss_label->setStyleSheet("font: 28pt \"宋体\";");
    compss_label->setText("指南针");
    //  文件夹
    folder = new Folder(tool_ui);
    folder->hide();
    //  设置
    set_arm = new Set_arm(tool_ui);
    set_arm->hide();
    //  倒车影像
    //camera = new Camera(tool_ui);
    //camera->hide();
#ifdef Q_OS_LINUX  // 这个宏由QT根据编译的平台自动定义
    //  灯
    led = new Led(this);
    led_state = false;
    //  六轴传感器
    icm20608 = new ICM20608(this);
    //  光、距离、红外传感器i
    ap3216c = new Ap3216c(this);
    //  WFi
    wifi = new Wifi(tool_ui);  //  会默认连接wifi
    wifi->hide();

    connect(wifi,&Wifi::wifi_judge,[=](bool judge){ //  获取wifi连接是否成功
        emit wifi_judge(judge);  // 这里第一个wifi_judge是wifi类的，第二个则是tool类的，也就是说在wifi触发信号后，会进一步去通知tool类的信号
    });
    connect(ap3216c,&Ap3216c::ap3216cDataChanged,[=]{  // 当发出ap3216cDataChanged信号时

        if(ap3216c->alsData().toInt() <= 5 || ap3216c->alsData().toInt() >= 700) // 当 Ap3216c 传感器检测到环境光亮度低于 5 或高于 700 时
        {
            if(led_big <= 0)
            {
                on_pushButton_light_clicked(); // 只要 led_big <= 0，就触发 on_pushButton_light_clicked()
                led_big=1;  // 设置 led_big = 1，避免 LED 反复开关。
            }
        }
    });
    connect(icm20608,&ICM20608::icm20608DataChanged,[=]{ // 当发出icm20608DataChanged信号（数据变化）时
        //  温度
        if(icm20608->tempData()>= 36)  // 根据温度，把把 label_temp_number 文字颜色变红或黑
        {
            ui->label_temp_number->setStyleSheet("color:red;");
        }
        else
        {
            ui->label_temp_number->setStyleSheet("color:black;");
        }
            ui->label_temp_number->setText(icm20608->tempData() + "℃"); // 再在文字最后加上摄氏度符号
        //  指南针数据改变
        float gxdata = icm20608->gxData().toFloat() * 10; // 获取 ICM20608 传感器的 X、Y 轴角速度数据
        float gydata = icm20608->gyData().toFloat() * 10;
        if(gxdata < 0) // 根据不同角度设置指南针方向
        {
            if(gydata < 0)
                compss->set_direction(180+sqrt((-gxdata)*(-gxdata)+(-gydata)*(-gydata)));
            else
                compss->set_direction(270+sqrt((-gxdata)*(-gxdata)+(-gydata)*(-gydata)));
        }else{
            if(gydata < 0)
                compss->set_direction(90+sqrt((-gxdata)*(-gxdata)+(-gydata)*(-gydata)));
            else
                compss->set_direction(sqrt((-gxdata)*(-gxdata)+(-gydata)*(-gydata)));
        }
    });
#endif
    //将 Set_arm 类中的 bizi_path 信号转发到当前对象，相当于建立了一个信号转发的机制。
    //当 Set_arm 对象的 bizi_path 信号被触发时，当前对象会响应并发出相同的 bizi_path 信号，同时携带信号参数 bizi_path_。
    connect(set_arm,&Set_arm::bizi_path,[this](QString bizi_path_){ 
                emit bizi_path(bizi_path_);
            });
    connect(set_arm,&Set_arm::use_name,[this](bool use_name_){
                emit use_name(use_name_);
            });
    //connect(camera,&Camera::close_camera,this,&Tool::hide_all);
}

Tool::~Tool()
{
    delete ui; 
}

void Tool::useName(bool use_name_xianshi)//  名字显示？
{
    if(use_name_xianshi)  //  显示
    {
        ui->label_backcar->show();
        ui->label_folder->show();
        ui->label_instructions->show();
        ui->label_light->show();
        ui->label_set->show();
        ui->label_wifi->show();
        compss_label->show();
    }
    else
    {
        ui->label_backcar->hide();
        ui->label_folder->hide();
        ui->label_instructions->hide();
        ui->label_light->hide();
        ui->label_set->hide();
        ui->label_wifi->hide();
        compss_label->hide();
    }
}

void Tool::hide_all() // 关闭
{
    textEdit_instructions->hide();
    folder->hide();
    //camera->close_camera();//  关闭摄像头
    //camera->hide();
    tool_ui->hide();
    set_arm->hide();
#ifdef Q_OS_LINUX
    wifi->hide();
#endif
}

void Tool::on_pushButton_folder_clicked() //文件夹被点击时触发的槽函数
{
    folder->show();
    tool_ui->show();
    emit hide_show_tool();
}

void Tool::on_pushButton_light_clicked() // 当灯的开关被点击时
{
#ifdef Q_OS_LINUX
    if(!led_state)   // 如果灯是关的
    {
        led->on_led_clicked(true); // 开灯
        ui->pushButton_light->setStyleSheet("border-image: url(:/car_terminall/light1.png);"); // 更改按钮样式，显示一个新图片
        led_state = true;  // 表示灯的状态是开启
    }
    else // 关灯
    {
        led->on_led_clicked(false);
        ui->pushButton_light->setStyleSheet("border-image: url(:/car_terminall/light0.png);");
        led_state = false;
    }
#endif
#ifdef Q_OS_WIN32
    qDebug()<<"\nWindow无法启用该模块!!!";
#endif
}

void Tool::on_pushButton_backcar_clicked()  // 倒车影像应该是
{
    //camera->show();
    //camera->open_camera();
    tool_ui->show();
    emit hide_show_tool();
}

void Tool::on_pushButton_wifi_clicked()  // wifi按钮被点击
{

#ifdef Q_OS_LINUX
    wifi->show();
    tool_ui->show();
    emit hide_show_tool();
#endif
#ifdef Q_OS_WIN32
    qDebug()<<"\nWindow无法启用该模块!!!";
#endif

}

void Tool::on_pushButton_instructions_clicked() // 使用介绍按钮被点击
{
    textEdit_instructions->show();
    tool_ui->show();
    emit hide_show_tool();

}

void Tool::on_pushButton_set_clicked()  // 设置按钮被点击
{
    set_arm->show();
    tool_ui->show();
    emit hide_show_tool();
}
