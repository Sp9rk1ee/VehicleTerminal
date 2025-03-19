#include "wifi.h"
#include "ui_wifi.h"

#include <QFileInfo>

Wifi::Wifi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Wifi)
{
    ui->setupUi(this);

    QFileInfo file("/home/root/shell/wifi"); //QFileInfo 用于获取文件或目录的元信息（如文件是否存在、大小、修改时间等）。

    if(!file.exists())
    {
        qDebug()<<"板子wifi初始化失败";
        return;
    }

    mima = new Mima(this,this);//实例化密码类


    process = new QProcess(this);//QProcess 是 Qt 提供的类，用于启动外部程序（如 shell 命令），并且可以与它们进行交互（例如，发送和接收数据）
    process->start("bash");//调用 start() 方法来启动一个外部程序。这里启动的是 bash，即一个 Linux 下的命令行 Shell。
    process->waitForStarted();//该方法会阻塞当前线程，直到 bash 进程成功启动并准备好运行。

    //execute_cmd("ifconfig wlan0 up",process);
    //execute_cmd("cd /home/root/shell/wifi",process);
    // 默认连接wifi名字： hdediannao 密码：122755hh
    //execute_cmd("source ./alientek_usb_wifi_setup.sh -m station -i hdediannao -p 122755hh -d wlan0");

    on_pushButton_clicked();//调用槽函数
    wifiNamemima = "hdediannao";

    timer_joint_wifi = new QTimer(this);//创建一个定时器
    timer_joint_wifi->start(60);//每60毫秒触发一次定时器事件

    connect(timer_joint_wifi,&QTimer::timeout,this,&Wifi::timeOut_timer_judge_wifi);//定时时间到就出发槽函数timeOut_timer_judge_wifi
    connect(mima,&Mima::wifimima,[=](QString wifimima){//当mima对象发射wifimima信号时（也就是界面上输入完wifi密码，点击ok）
        //qDebug()<<wifimima;
        execute_cmd("ifconfig wlan0 up",process);//在shell（前面的process）中敲入ifconfig wlan0 up命令，用来启动 wlan0 网络接口
        execute_cmd(QString("source ./alientek_usb_wifi_setup.sh -m station -i %1 -p %2 -d wlan0").arg(wifiNamemima).arg(wifimima),process);//设置wifi
        timer_joint_wifi->start(50);//启动一个50毫秒的定时器
    });
}

Wifi::~Wifi()
{
    delete ui;
}
//当刷新按钮被点击时触发的槽函数
void Wifi::on_pushButton_clicked()
{
    execute_cmd("cd /home/root/shell/wifi",process);//这行代码通过 QProcess 执行 cd /home/root/shell/wifi 命令，切换当前的工作目录
    //扫描当前无线网卡（wlan0）周围的 WiFi 网络。扫描结果被重定向到一个名为 wifiinfo 的文件中，保存在当前工作目录下
    execute_cmd("iwlist wlan0 scan > ./wifiinfo",process);

    QFile wifiinfo("//home/root/shell/wifi/wifiinfo");//QFile 用于直接操作文件（打开、读取、写入、关闭等）。
    if(!wifiinfo.open(QFile::ReadOnly)){//以只读模式打开文件
        return;
    }

    QTextStream in(&wifiinfo);//QTextStream 是一个用于读取和写入文本文件的工具类
    while(!in.atEnd())  // 一行一行一直读，直至读取失败
    {
        QString data = in.readLine().toUtf8();//读取一行存到data里,将其转换为 UTF-8 编码的 QString 类型
        if(data.contains("ESSID"))//检查当前读取的这一行是否包含 ESSID 字符串。ESSID 是 WiFi 网络的名称标识符，表示网络的名称
        {
            //如果当前行包含 ESSID，则通过 split(":") 方法将这一行按照冒号 : 分割，获取 WiFi 名称部分（即冒号后面的内容）。并将其存储在 wifiname_ 变量中
            QString wifiname_=data.split(":").at(1);
            ui->listWidget->addItem(wifiname_.remove("\""));//将 WiFi 名称（去除双引号）添加到 listWidget 控件中显示出来
        }

    }
    wifiinfo.close();//文件读取完毕后，关闭 wifiinfo 文件
}

void Wifi::execute_cmd(QString text,QProcess *process)
{
    if(process->waitForStarted())//等待进程启动成功
    {
        qDebug()<<"Connected to terminal";
        /*确保命令后面有换行符 \n，让 shell 正确执行。
        转换 QString 到 Latin-1 编码，确保 shell 能正确解析字符串。
        获取底层 char* 数据指针，以便 QProcess::write() 发送到外部进程。
        通过 write() 将命令输入到 QProcess 进程，就像手动在终端输入命令并按 Enter 一样。*/
        process->write((text+"\n").toLatin1().data());
        process->waitForReadyRead();//等待bash执行完命令（可读）
        //QByteArray outPut = process->readAllStandardOutput();
        //qDebug()<<outPut;

//        QEventLoop loop;//定义一个新的事件循环
//        QTimer::singleShot(50,&loop,SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
//        loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
    }
    else
    {
        qDebug()<<"Failed to connect to terminal";
    }
}

//wifi旁边那个点点按钮被点击时触发
void Wifi::on_radioButton_toggled(bool checked)
{
    if(checked == true)//如果是选中的
    {  // 选中状态
        on_pushButton_clicked();//调用槽函数更新wifi列表
//        mima->show();
//        mima->getmima("aaa");
    }
    else
    {  // 不选状态
        ui->listWidget->clear();
    }
}

//当wifi列表中的某一项被点击时触发
void Wifi::on_listWidget_itemClicked(QListWidgetItem *item)
{
    wifiNamemima = item->text();//获取被点击项的文本内容，并赋值给wifiNamemima
    //wifiNamemima = "\""+wifiNamemima+"\"";
    mima->show();//显示mima窗口
    mima->getmima(wifiNamemima);//调用getmima函数，吧wifiNamemima显示在lineedit
}

//定时器时间到时触发
void Wifi::timeOut_timer_judge_wifi()
{
    timer_joint_wifi->stop();// 停止定时器，防止重复触发

    QFile wifiinfo("//home/root/shell/wifi/wifiinfo");// 打开存储 Wi-Fi 信息的文件
    if(!wifiinfo.open(QFile::ReadOnly)){//以只读方式打开
        qDebug()<<"wifi查看失败";
        return;
    }
    QTextStream in(&wifiinfo);//QTextStream 是一个用于读取和写入文本文件的工具类
    bool you=false;
    while(!in.atEnd())  // 一行一行一直读，直至读取失败
    {
        QString data = in.readLine();//读取一行存到data里
        if(data.contains("ESSID"))//检查当前读取的这一行是否包含 ESSID 字符串。ESSID 是 WiFi 网络的名称标识符，表示网络的名称
        {
            QString namewifi_=data.split(":").at(1);//获取wifi名称
            if(namewifi_.remove("\"") == wifiNamemima){//如果当前这一行的wifi名称和目前wifi名称一样
                emit wifi_judge(true); //  有wifi 发送信号，表示有wifi
                you = true;

                qDebug()<<data.split(":").at(1)<<"wifi链接成功";
                wifiinfo.close();

                return;
            }


        }
    }
    if(!you)//如果没有，则发送没wifi的信号
        emit wifi_judge(false);

    wifiinfo.close();

    //process->close();
}
