#include "mima.h"
#include "ui_mima.h"

Mima::Mima(QWidget *parent,QWidget *parent1) :
    QDialog(parent),
    ui(new Ui::Mima)
{
    ui->setupUi(this);

    softKeyboard = new SoftKeyboard(parent1); //新建一个Softketboard对象（键盘）
    softKeyboard->raise();// 把这个对象置于顶层
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    /*ui->lineEdit 和 ui->lineEdit_2 是 QLineEdit 输入框。
    installEventFilter(this) 将 Mima 作为它们的事件过滤器。
    之后，每当 lineEdit 或 lineEdit_2 发生事件（如鼠标点击、按键输入等），这些事件都会先传递给 Mima 窗口的 eventFilter 函数*/
}

Mima::~Mima()
{
    delete ui;
}

void Mima::getmima(QString wifiName)
{
    ui->lineEdit->setText(wifiName);//将wifi名称显示在lineEdit中
}

bool Mima::eventFilter(QObject *watched, QEvent *event)// watch是当前正在监视的对象    event是发生的事件
{
    if(event->type()==QEvent::MouseButtonRelease)// 判断事件类型是否是鼠标按钮释放事件
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);// 将事件强制转换为 QMouseEvent 类型
        if(mouseEvent->button() == Qt::LeftButton)//判断鼠标按键是不是左键
        {
            QPoint point = this->pos();// 获取当前窗口的位置
            if(watched == ui->lineEdit)// 判断事件是否发生在 lineEdit 控件上
            {
                connect(softKeyboard,&SoftKeyboard::sendInputBufferAreaText,this,[=](QString textt){
                    ui->lineEdit->setText(textt);
                });// 将软键盘输入的文本设置到 lineEdit 上
                softKeyboard->showInputBufferArea("Please Input:");//显示提示文本，在软键盘区域上
                softKeyboard->resize(600,320);//设置软键盘的大小
                softKeyboard->move(point+ui->lineEdit->pos());//将软键盘放在一个特定位置
                softKeyboard->show();//显示软键盘
            }else if(watched == ui->lineEdit_2)// 判断事件是否发生在 lineEdit2 控件上
            {
                connect(softKeyboard,&SoftKeyboard::sendInputBufferAreaText,this,[=](QString textt){
                    ui->lineEdit_2->setText(textt);
                });
                softKeyboard->showInputBufferArea("Please Input:");
                softKeyboard->resize(600,320);
                softKeyboard->move(point+ui->lineEdit_2->pos());
                softKeyboard->show();
            }
        }
    }
    //这行代码的作用是确保在自定义事件处理之后，事件能够继续传递给父类的处理函数。
    //这样保证了事件的处理不会被完全中断，可以同时处理自定义逻辑和默认的事件行为。
    return QWidget::eventFilter(watched,event);//返回父类的事件过滤器
}

//当用户点击对话框中的 "OK" 按钮时，获取 lineEdit_2 控件中的文本（即用户输入的内容），并通过 wifimima 信号发射出去。
void Mima::on_buttonBox_accepted()
{
    emit wifimima(ui->lineEdit_2->text());
}
