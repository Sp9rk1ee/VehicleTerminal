#include "pitherbig.h"
#include "ui_pitherbig.h"

PitherBig::PitherBig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PitherBig)
{
    ui->setupUi(this);

    QPalette pal = palette();//创建了一个 QPalette 对象 pal，用于设置窗口的背景颜色
    pal.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));//设置背景色为透明
    setPalette(pal);//应用新的调色板,调用这个函数之后，控件的颜色将根据 pal 中的设置来显示。
    setWindowOpacity(1);//设置窗口的透明度为 1

    timerdoubleClock = new QTimer(this);
    // 按键
    pushButton_left = new QPushButton(this);
    pushButton_right = new QPushButton(this);
    //  单个使用
    //pushButton_left->setStyleSheet("border-image: url(:/previous_hover.png);");
    //pushButton_right->setStyleSheet("border-image: url(:/next_hover.png);");
    //  整体使用
    pushButton_left->setStyleSheet("border-image: url(:/photoViem/previous_hover.png);");
    pushButton_right->setStyleSheet("border-image: url(:/photoViem/next_hover.png);");
    pushButton_left->setFixedSize(70,70);
    pushButton_right->setFixedSize(70,70);
    pushButton_left->raise();//置于最上层
    pushButton_right->raise();
    pushButton_left->hide();
    pushButton_right->hide();

    connect(pushButton_left,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_left1(bool)));
    connect(pushButton_right,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_right1(bool)));
    connect(timerdoubleClock,SIGNAL(timeout()),timerdoubleClock,SLOT(stop()));//计时器到就停止
}

PitherBig::~PitherBig()
{
    delete ui;
}

void PitherBig::showPixmap(QPixmap showPixmap)
{   //这一行代码将传入的 QPixmap showPixmap 按照当前窗口（this）的宽度和高度进行缩放。
    showPixmap = showPixmap.scaled(this->width(), this->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(showPixmap);//显示图片
    item_number = pixmapData.indexOf(showPixmap);//查找 showPixmap 在 pixmapData 中的位置，并将其索引赋值给 item_number。
}

//切换上一张图片显示，当左按钮被点击时触发
void PitherBig::on_pushButton_left1(bool)
{
    item_number--;
    if(item_number < 0) item_number = pixmapData.size()-1;
    ui->label->setPixmap(pixmapData[item_number]);
}

//下一张
void PitherBig::on_pushButton_right1(bool)
{
    item_number++;
    if(item_number >= pixmapData.size()) item_number = 0;
    ui->label->setPixmap(pixmapData[item_number]);
}

//将传入的 QPixmap 对象进行缩放处理，并将其存储到 pixmapData 容器中。
void PitherBig::getPixmapData(QPixmap PixmapData)
{   //对传入的 PixmapData 图片进行缩放
    PixmapData = PixmapData.scaled(this->width(), this->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pixmapData.append(PixmapData);//将缩放后的图片添加到 pixmapData 容器中。
}

//当用户鼠标点击时自动调用，这里的调用是在放大状态下点击时才是调用这个函数，用于把放大的那个图片隐藏
void PitherBig::mousePressEvent(QMouseEvent *event)
{
     // 如果是鼠标左键按下
     if(event->button() == Qt::LeftButton)
     {
         if(!timerdoubleClock->isActive())//检查定时器 timerdoubleClock 是否处于活动状态。如果定时器没有激活，表示用户第一次点击。
         {
             if(pushButton_left->isHidden())//如果是隐藏的，则把左右两个按钮显示
             {
                 pushButton_left->setGeometry(20, this->height()/2 - pushButton_left->width()/2, pushButton_left->width(), pushButton_left->width());
                 pushButton_right->setGeometry(this->width() - pushButton_right->width()-20, this->height()/2 - pushButton_left->width()/2, pushButton_left->width(), pushButton_left->width());
                 pushButton_left->show();
                 pushButton_right->show();
             }
             else//否则，把左右两个按钮隐藏
             {
                 pushButton_left->hide();
                 pushButton_right->hide();
             }
             timerdoubleClock->start(1000);//开启定时器
         }
         else//否则，说明是在一秒内连续按下的
         {
             emit hide_();
         }

     }
     // 如果是鼠标右键按下
//     else if(event->button() == Qt::RightButton)
//     {
     //     }
}

