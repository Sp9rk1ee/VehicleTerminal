#include "form.h"
#include "ui_form.h"
#include <QDebug>



//form.cpp好像没啥用，只是单纯测试softkeyboard的

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    //ui->setupUi(this);
    softKeyboard = new SoftKeyboard();//创建一个键盘
    ui->lineEdit->installEventFilter(this);//给lineedit注册事件过滤器，当lineedit发生事件的时候（如鼠标点击），会触发eventFilter函数
    ui->lineEdit_2->installEventFilter(this);
}

Form::~Form()
{
    delete ui;
}
//事件过滤器处理函数
bool Form::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonRelease)//事件类型，如果是鼠标释放类型
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);//将事件强制转换
        if(mouseEvent->button() == Qt::LeftButton)//如果是左键
        {
            QPoint point = this->pos();
            if(watched == ui->lineEdit)//如果点击的是lineEdit
            {
                softKeyboard->hideInputBufferArea(ui->lineEdit);//隐藏输入缓冲区
                softKeyboard->resize(600,320);
                softKeyboard->move(point+ui->lineEdit->pos());
                softKeyboard->show();
            }
            else if(watched == ui->lineEdit_2)
            {
                connect(softKeyboard,SIGNAL(sendInputBufferAreaText(QString)),this,SLOT(setLineEdit_2Text(QString)));
                softKeyboard->showInputBufferArea("Please Input:");
                softKeyboard->resize(600,320);
                softKeyboard->move(point+ui->lineEdit_2->pos());
                softKeyboard->show();
            }
        }
    }
    return QWidget::eventFilter(watched,event);//返回父类的事件过滤器
}


void Form::setLineEdit_2Text(QString text)
{
    ui->lineEdit_2->setText(text);
}

