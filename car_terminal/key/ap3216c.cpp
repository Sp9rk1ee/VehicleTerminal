#include "ap3216c.h"

#include <QDebug>
#include <fcntl.h>       // open(*filename,O_RDONLY)  用
#include <unistd.h>      // close(int)  用

Ap3216c::Ap3216c(QObject *parent)
    : QObject{parent}
{
    timerr = new QTimer();//定时器
    timerr->start(500);
    connect(timerr,SIGNAL(timeout()),this,SLOT(timer_timeout()));//每次定时时间到就从传感器读一次新数据
}

Ap3216c::~Ap3216c()
{
    timerr->stop();
    delete timerr;
}

//定时器定时时间到就触发，读取一次新数据
void Ap3216c::timer_timeout()
{
    //qDebug()<<"获取数据";
    alsdata = readAlsData();
    psdata  = readPsData();
    irdata  = readIrData();
    emit ap3216cDataChanged();
}


QString Ap3216c::alsData()
{
    return alsdata;
}

QString Ap3216c::psData()
{
    return psdata;
}

QString Ap3216c::irData()
{
    return irdata;
}

//读取光照强度
QString Ap3216c::readAlsData()
{
    char const *filename="/sys/class/misc/ap3216c/als";
    int err = 0;
    int fd;
    char buf[10];

    fd = open(filename,O_RDONLY);
    if(fd<0)
    {
        close(fd);
        return "open file error";
    }

    err = read(fd,buf,sizeof (buf));
    if(err<0)
    {
        qDebug()<<err;
        close(fd);
        return "read data error";
    }
    close(fd);

    QString alsValue = buf;
    QStringList list = alsValue.split("\n");
    return list[0];
}

//读取距离
QString Ap3216c::readPsData()
{
    char const *filename = "/sys/class/misc/ap3216c/ps";
    int err = 0;
    int fd;
    char buf[10];

    fd = open(filename,O_RDONLY);
    if(fd<0)
    {
        close(fd);
        return "open file error";
    }

    err = read(fd,buf,sizeof (buf));
    if(err<0)
    {
        qDebug()<<err;
        close(fd);
        return "read data error";
    }
    close(fd);

    QString psValue = buf;
    QStringList list = psValue.split("\n");
    //qDebug()<<list;
    return list[0];
}

//红外
QString Ap3216c::readIrData()
{
    char const *filename="/sys/class/misc/ap3216c/ir";
    int err = 0;
    int fd;
    char buf[10];

    fd = open(filename,O_RDONLY);
    if(fd<0)
    {
        close(fd);
        return "open file error";
    }

    err = read(fd,buf,sizeof (buf));
    if(err<0)
    {
        qDebug()<<err;
        close(fd);
        return "read data error";
    }
    close(fd);

    QString irValue = buf;
    QStringList list = irValue.split("\n");
    return list[0];
}

