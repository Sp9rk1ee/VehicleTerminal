#include "key.h"
#include "ui_key.h"
#include <QDebug>

//估计是没做完这个
Key::Key(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Key)
{
    //ui->setupUi(this);

    //ap3216c = new Ap3216c(this);

    //connect(ap3216c,SIGNAL(ap3216cDataChanged()),this,SLOT(getAp3216cData()));
}

Key::~Key()
{
    delete ui;
}

void Key::keyPressEvent_1(QKeyEvent *event)
{

#if __arm__  // 这个会根据编译时候的目标平台自动生成宏定义，这是arm架构
    if(event->key() == Qt::Key_VolumeDown)  // 如果按下的键是音量降低键
    {
        //this->setStyleSheet("QWidget {background-color: red}");
        qDebug()<<"按键按下arm";
    }
#else
    if(event->key() == Qt::Key_Down) //  如果按下的键是方向中的下键
    {
        //this->setStyleSheet("QWidget {background-color: red}");
        qDebug()<<"按键按下arm";
    }
#endif
}

void Key::keyReleaseEvent_1(QKeyEvent *event)
{
#if __arm__
    if(event->key() == Qt::Key_VolumeDown) // 和上面同理
    {
        //this->setStyleSheet("QWidget {background-color: red}");
        emit main_show(); // 发送main_show（）信号,会触发exit_all()
        qDebug()<<"按键松开arm";
    }
#else
    if(event->key() == Qt::Key_Down) //  下键
    {
        //this->setStyleSheet("QWidget {background-color: red}");
        emit main_show();
        qDebug()<<"按键松开arm";
    }
#endif
}

void Key::keyPressEvent(QKeyEvent *event)
{
#if __arm__
    if(event->key() == Qt::Key_VolumeDown)
    {
        //this->setStyleSheet("QWidget {background-color: red}");
        qDebug()<<"按键按下";
    }
#else
    if(event->key() == Qt::Key_Down) //  下键
    {
        //this->setStyleSheet("QWidget {background-color: red}");
        qDebug()<<"按键按下";
    }
#endif
    qDebug()<<"按键";
    QWidget::keyPressEvent(event);
}

void Key::keyReleaseEvent(QKeyEvent *event)
{
#if __arm__
    if(event->key() == Qt::Key_VolumeDown)
    {
        //this->setStyleSheet("QWidget {background-color: red}");
        qDebug()<<"按键松开";
    }
#else
    if(event->key() == Qt::Key_Down) //  下键
    {
        //this->setStyleSheet("QWidget {background-color: red}");
        qDebug()<<"按键松开";
    }
#endif
    QWidget::keyPressEvent(event);
}

void Key::getAp3216cData()
{
    qDebug()<<"刷新数据";
    //qDebug()<<
//    ui->label_3->setText(ap3216c->alsData());
//    ui->progressBar->setValue(ap3216c->alsData().toUInt() / 3);
//    ui->label_5->setText(ap3216c->psData());
//    ui->progressBar_2->setValue(ap3216c->psData().toUInt() / 8);
//    ui->label_7->setText(ap3216c->irData());
//    ui->progressBar_3->setValue(ap3216c->irData().toUInt());
}

