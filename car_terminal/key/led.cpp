#include "led.h"
#include <QDebug>

//控制led和蜂鸣器的开关，很简单
Led::Led(QWidget *parent)
    : QWidget(parent)
{
/*    ui->radioButton->setStyleSheet("QRadioButton::indicator{width:20px;height:20px;color:rgb(0,0,0)}\
*                                   QRadioButton{font-size:16px;;color:rgb(0,0,0);}\
*                                   QRadioButton::checked{color:rgb(0,0,0);}\
*                                   QRadioButton::unchecked{color:rgb(255,255,255)}\
*                                   ");
*    ui->radioButton_2->setStyleSheet("QRadioButton::indicator{width:20px;height:20px;color:rgb(0,0,0)}\
*                                   QRadioButton{font-size:16px;;color:rgb(0,0,0);}\
*                                   QRadioButton::checked{color:rgb(0,0,0);}\
*                                   QRadioButton::unchecked{color:rgb(255,255,255)}\
*                                   ");
*/

   //开发板的led接口
   fileled.setFileName("/sys/class/leds/sys-led/brightness");//设置 file 这个 QFile 对象所关联的文件路径，但不会立即打开文件
   if(fileled.exists()) //  判断是否存在，随便可以知道是板子还是虚拟机
   {
       //改变LED触发方式，改为none,（无）
       system("echo none > /sys/class/leds/sys-led/trigger");//关闭led的自动触发
       filebeep.setFileName("/sys/class/leds/beep/brightness");
   }
   qDebug()<<"LED打开失败";
}

Led::~Led()
{

}

void Led::on_beep_clicked(bool checked)
{
    if(!filebeep.exists())
    {
        //QMessageBox::information(this,"端口检查","没有检查到对应端口");
        filebeep.close();
        qDebug()<<"LED检查失败";
        return;
    }
    //qDebug()<<"LED检查成功";

    //打开文件
    if(!filebeep.open(QIODevice::WriteOnly))
    {
        return;
    }

    QByteArray buf[] = {"0","1"};

    if(checked)
    {//开led1
        filebeep.write(buf[1]);
    }
    else
    {//关led1
        filebeep.write(buf[0]);
    }

    filebeep.close();
}

void Led::on_led_clicked(bool checked)
{
    if(!fileled.exists())
    {
        //QMessageBox::information(this,"端口检查","没有检查到对应端口");
        filebeep.close();
        qDebug()<<"LED检查失败";
        return;
    }
    //qDebug()<<"LED检查成功";

    //打开文件
    if(!fileled.open(QIODevice::WriteOnly))
    {
        return;
    }

    QByteArray buf[] = {"0","1"};

    if(checked)
    {//开led1
        fileled.write(buf[1]);
    }
    else
    {//关led1
        fileled.write(buf[0]);
    }

    fileled.close();
}


