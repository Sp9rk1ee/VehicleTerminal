#include "photoviem.h"
#include "ui_photoviem.h"

PhotoViem::PhotoViem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PhotoViem)
{
    ui->setupUi(this);

    widget_photo = new MyListWidget(this);
    widget_photo->setStyleSheet("font: 15pt \"宋体\";color: rgb(255, 255, 255);background-color: rgb(109, 109, 109);");
    widget_photo->resize(this->width()/4,this->height());
    widget_photo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    // 隐藏滚动条（水平）
    widget_photo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);      // 隐藏滚动条（垂直）

    // 按键
    pushButton_left = new QPushButton(this);
    pushButton_right = new QPushButton(this);

    //  整体使用（否则按键没图标）
    pushButton_left->setStyleSheet("border-image: url(:/photoViem/previous_hover.png);");
    pushButton_right->setStyleSheet("border-image: url(:/photoViem/next_hover.png);");

    pushButton_left->setFixedSize(70,70);
    pushButton_right->setFixedSize(70,70);
    pushButton_left->raise();//置于顶层
    pushButton_right->raise();
    pushButton_left->hide();
    pushButton_right->hide();

    item_number = 0;

    scanPicture();  //  遍历图片

    pitherBig = new PitherBig(this);
    for (int i = 0; i < pixmapData.size(); ++i) {
        pitherBig->getPixmapData(pixmapData[i]);
    }

    pitherBig->hide();

    timerConversion = new QTimer(this);
    timerdoubleClick = new QTimer(this);

    // 默认显示第一张
    ui->label_picture->setPixmap(pixmapData[0]);
    timerConversion->start(3);

    connect(widget_photo,&MyListWidget::itemClicked,this,&PhotoViem::on_listWidget_photo_itemClicked);
    connect(pushButton_left,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_left0(bool)));
    connect(pushButton_right,&QPushButton::clicked,this,&PhotoViem::on_pushButton_right0);
    connect(pitherBig,&PitherBig::hide_,this,&PhotoViem::show_widget);
    connect(timerdoubleClick,SIGNAL(timeout()),timerdoubleClick,SLOT(stop()));
    connect(timerConversion,&QTimer::timeout,[=]{
        on_pushButton_right0(true);
        emit at_pixmap(pixmapData[item_number]);
    });
}

PhotoViem::~PhotoViem()
{
    delete ui;
    delete pitherBig;
}

void PhotoViem::hide__()
{
    show_widget();
    hide();
}

void PhotoViem::scanPicture()
{
    widget_photo->clear();

    QDir dir(QCoreApplication::applicationDirPath() + "/myAlbum");//目录
    QDir dirbsolutePath(dir.absolutePath());
    // 目录存在？
    if(!dirbsolutePath.exists())
    {
        qDebug()<<"Errpr 目录不存在"<<dir;
        return;
    }

    QStringList filter; // 定义过滤器
    filter << "*.jpg" << "*.jpeg" << "*.png";
    // 获取目录下的文件
    QFileInfoList files = dirbsolutePath.entryInfoList(filter,QDir::Files);

    for(int i = 0; i< files.count(); i++)
    {
        // 使用utf-8
        QString name_picture = QString::fromUtf8(files.at(i).fileName().toUtf8().data());//获取图片文件名
        QString path_picture = QString::fromUtf8(files.at(i).filePath().toUtf8().data());//获取路径
        QPixmap pixmap(path_picture);//使用 QPixmap 加载图片
        //qDebug()<<ui->label_picture->width()<<ui->label_picture->height()<<this->width()<<this->height();
        pixmap = pixmap.scaled(this->width()*4/5, this->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);//调整大小
        // 添加到内容数组里储存
        pixmapData.append(pixmap);
        // 添加名字到列表
        widget_photo->addItem(name_picture + "\n");
    }
}

void PhotoViem::show_widget()
{
    pitherBig->hide();
}

void PhotoViem::mousePressEvent(QMouseEvent *event)
{
     // 如果是鼠标左键按下
     if(event->button() == Qt::LeftButton)
     {
         if(!timerdoubleClick->isActive())//检查定时器是否在活动状态，如果定时器没有激活，表示用户第一次点击。则只是单纯的隐藏或显示左右按钮
         {
             if(pushButton_left->isHidden())//如果左右两个按钮是隐藏的，把它们显示
             {
                 pushButton_left->setGeometry(ui->widget_picture->x()+20, this->height()/2 - pushButton_left->width()/2, pushButton_left->width(), pushButton_left->width());
                 pushButton_right->setGeometry(this->width() - pushButton_right->width()-20, this->height()/2 - pushButton_left->width()/2, pushButton_left->width(), pushButton_left->width());
                 pushButton_left->show();
                 pushButton_right->show();
             }
             else//否则，把他们隐藏
             {
                 pushButton_left->hide();
                 pushButton_right->hide();
             }
             timerdoubleClick->start(1000);
         }
         else//如果定时器激活了，说明是在一秒内重复点击了，则放大图片显示
         {
             pitherBig->showPixmap(pixmapData[item_number]);//把图片放大显示
             pitherBig->show();
         }
     }
     // 如果是鼠标右键按下
//     else if(event->button() == Qt::RightButton)
//     {
     //     }
}

//切换到上一个图片显示
void PhotoViem::on_pushButton_left0(bool )
{
    item_number--;
    if(item_number < 0) item_number = pixmapData.size()-1;
    ui->label_picture->setPixmap(pixmapData[item_number]);
    widget_photo->setCurrentRow(item_number);
    timerConversion->start(3000);
}

//切换到下一个图片显示
void PhotoViem::on_pushButton_right0(bool )
{
    item_number++;
    if(item_number >= pixmapData.size()) item_number = 0;
    ui->label_picture->setPixmap(pixmapData[item_number]);
    widget_photo->setCurrentRow(item_number);
    timerConversion->start(3500);
}

//图片列表中的某一项被点击时触发，更换显示的图片
void PhotoViem::on_listWidget_photo_itemClicked(QListWidgetItem *item)
{
    item_number = widget_photo->row(item);
    ui->label_picture->clear();
    ui->label_picture->setPixmap(pixmapData[item_number]);
    timerConversion->start(3500);
}
