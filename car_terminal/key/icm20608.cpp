#include "icm20608.h"

#include <QDebug>
#include <fcntl.h>       // open(*filename,O_RDONLY)  用
#include <unistd.h>      // close(int)  用

ICM20608::ICM20608(QObject *parent)
    : QObject{parent}
{

    timerr = new QTimer(this);
    timerr->start(500);
    connect(timerr,SIGNAL(timeout()),this,SLOT(timer_timeout()));//定时器定时到更新数据

}

ICM20608::~ICM20608()
{

}

void ICM20608::timer_timeout()
{
    icm20608ReadData();
}

QString ICM20608::gxData()
{
    return gxdata;
}

QString ICM20608::gyData()
{
    return gydata;
}

QString ICM20608::gzData()
{
    return gzdata;
}

QString ICM20608::axData()
{
    return axdata;
}

QString ICM20608::ayData()
{
    return aydata;
}

QString ICM20608::azData()
{
    return azdata;
}

QString ICM20608::tempData()
{
    return tempdata;
}

//定时器定时到时触发
void ICM20608::icm20608ReadData()
{
    int fd;
    char const *filename = "/dev/icm20608";
    int databuf[7];
    //unsigned char data[14];
    int gyor_x_adc, gyor_y_adc, gyor_z_adc;//角速度原始值
    int accel_x_adc, accel_y_adc, accel_z_adc;//加速度原始值
    int temp_adc;//温度原始值

    float gyor_x_act, gyor_y_act, gyor_z_act;//角速度实际值（经过原始值转换得到）
    float accel_x_act, accel_y_act, accel_z_act;////加速度实际值（经过原始值转换得到）
    float temp_act;//温度实际值

    int ret =0;

    fd = open(filename,O_RDWR);
    if(fd<0)
    {
        timerr->stop();
        qDebug()<<QString("can‘t open file %1").arg(filename);
        return;
    }
    ret = read(fd,databuf,sizeof(databuf));

    // 读取成功
    if(ret ==0)
    {
        gyor_x_adc = databuf[0];
        gyor_y_adc = databuf[1];
        gyor_z_adc = databuf[2];
        accel_x_adc = databuf[3];
        accel_y_adc = databuf[4];
        accel_z_adc = databuf[5];
        temp_adc = databuf[6];

        //实际值
        gyor_x_act= (float)(gyor_x_adc ) / 16.4;
        gyor_y_act= (float)(gyor_y_adc ) / 16.4;
        gyor_z_act= (float)(gyor_z_adc ) / 16.4;
        accel_x_act =(float)(accel_x_adc) / 2048;
        accel_y_act =(float)(accel_y_adc) / 2048;
        accel_z_act =(float)(accel_z_adc) / 2048;
        temp_act = ((float)(temp_adc)-25) / 326.8 +25;

        gxdata = QString::number(gyor_x_act,'f',2);//把浮点数转换成字符串，并保留两位小数
        gydata = QString::number(gyor_y_act,'f',2);
        gzdata = QString::number(gyor_z_act,'f',2);
        axdata = QString::number(accel_x_act,'f',2);
        aydata = QString::number(accel_y_act,'f',2);
        azdata = QString::number(accel_z_act,'f',2);
        tempdata = QString::number(temp_act,'f',2);
    }
    close(fd);
    emit icm20608DataChanged();
}

