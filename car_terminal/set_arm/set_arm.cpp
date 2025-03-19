#include "set_arm.h"
#include "ui_set_arm.h"


// Set_arm 主要用于 管理和切换壁纸，并控制文本显示状态。
Set_arm::Set_arm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Set_arm)
{
    ui->setupUi(this);

    setting = new QLabel(this); //创建一个QLabel，用于显示壁纸
    setting->setPixmap(QPixmap("./bizi/1.png")); //加载 ./bizi/1.png 作为默认壁纸
    setting->setScaledContents(true); //让图片自动适应 QLabel 的大小。
    setting->lower();//把 setting 放到最底层，防止它遮挡其他 UI 元素
    setting->resize(this->size());//this->size() 获取当前 Set_arm 窗口的大小。

    //  遍历壁纸
    QDir dir(QCoreApplication::applicationDirPath() + "/bizi");// 获得一个路径赋值给dir
    QDir dirbsolutePath(dir.absolutePath());// 获得dir的绝对路径赋值给dirbsolutePath
    // 目录存在？
    if(!dirbsolutePath.exists())
    {
        qDebug()<<"壁纸文件夹目录不存在";
        return;
    }
    QStringList filter; // 定义过滤器
    filter << "*.jpg"<< "*.png"; // 过滤器会过滤出jpg和png文件
    // 获取目录下的文件
    QFileInfoList files = dirbsolutePath.entryInfoList(filter,QDir::Files);//在dir目录中过滤出符合条件的文件，Files表示仅返回普通文件，不包括目录

    for(int i = 0; i< files.count(); i++) // 遍历获得的文件列表
    {
        QString path = files.at(i).fileName(); // 将每一个文件的文件名存在path中
        bizi_path_list.append("./bizi/"+path); //把获得的文件名path和/bizi/合起来组成一个新路径加到bizi_path_list列表中
    }

    //  设置默认状态
    use_name_ = true; //  应用名字显示
    bizi_number =0;
}

Set_arm::~Set_arm()
{
    delete ui;
}

// pushButton_wallpaper按钮按下时触发
void Set_arm::on_pushButton_wallpaper_clicked()
{
    bizi_number++; //增加当前索引号
    if(bizi_number>=bizi_path_list.size())bizi_number=0;
    emit bizi_path(bizi_path_list.at(bizi_number));// 发射信号，信号的参数是当前文件的路径
    setting->setPixmap(QPixmap(bizi_path_list.at(bizi_number)));// 设置要显示的壁纸图片
    setting->setScaledContents(true);// 启动自适应大小
}


void Set_arm::on_pushButton_use_text_clicked()
{
    if(use_name_)
    {
        ui->pushButton_use_text->setText("隐藏");
        emit use_name(false);//发送信号，隐藏
        use_name_ = false;
    }
    else
    {
        ui->pushButton_use_text->setText("显示");
        emit use_name(true);// 发送信号，显示
        use_name_ = true;
    }
}

