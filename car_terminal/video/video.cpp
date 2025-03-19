#include "video.h"
#include "ui_video.h"

#include <QFile>
#include <QDir>

Video::Video(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Video)
{
    ui->setupUi(this);

    // 背景
    QPalette pal = this->palette();//QPalette 用来管理控件的颜色、背景等样式。
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/video_pic/bg.png")));//通过 QBrush 和 QPixmap 设置了背景图片
    setPalette(pal);//将一个 QPalette 对象应用到当前控件上，改变控件的外观

    // 视频控件绑定,设置
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayerList = new QMediaPlaylist(this);
    videoWidget = new QVideoWidget(this);
    mediaPlayer->setVideoOutput(videoWidget);//将 mediaPlayer 的视频输出设置为 videoWidget
    mediaPlayer->setPlaylist(mediaPlayerList);//将播放列表 mediaPlayerList 赋值给播放器。
    ui->verticalLayout->addWidget(videoWidget);//将视频控件 videoWidget 添加到界面布局 verticalLayout 中。

    videoWidget->setAutoFillBackground(true);  // 是否填充背景
    mediaPlayer->setVolume(50);//设置视频播放器的音量

    // 视频目录
    listWidget_catalog = new MyListWidget(this);//视频目录控件
    listWidget_catalog->setGeometry(0,0,this->width()*2 / 5,this->height());//设置大小和位置
    listWidget_catalog->raise();  // 置于最上层
    listWidget_catalog->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 隐藏滚动条（水平）
    listWidget_catalog->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // 隐藏滚动条（垂直）
    listWidget_catalog->setStyleSheet("background-color: rgb(89, 89, 89);color: rgb(230, 230, 230);font: 17pt \"爱奇艺黑体\";");//背景颜色和字体
    listWidget_catalog->hide();
    timer_catalog = new QTimer(this);//创建了一个计时器 timer_catalog，用来控制目录控件的显示时间。

    // 声音调节控件
    slider_Sound = new QSlider(Qt::Vertical,this);//创建了一个垂直的声音调节滑块 slider_Sound
    slider_Sound->setValue(50);//设置其初始值为 50
    slider_Sound->setStyleSheet("border-image: url(:/images/video_pic/sub-page1.png);");//设置了滑块的样式为某张图片
    slider_Sound->hide();//隐藏
    label_Sound = new QLabel(this);//创建了一个 QLabel 用于显示当前音量值
    label_Sound->setStyleSheet("color: rgb(250, 250, 250);font: 12pt \"爱奇艺黑体\";");
    label_Sound->setText("50");//默认显示 "50"
    label_Sound->hide();//隐藏
    timer_Sound = new QTimer(this);//创建一个定时器，用于控制音量控制按钮的显示时间

    item_number = 0;  // 初始化视频项数 item_number 为 0。

    scanVideos();//调用 scanVideos() 函数扫描视频文件
    mediaPlayerList->setCurrentIndex(0);//设置播放列表的当前索引为 0
    //mediaPlayer->play();

    connect(listWidget_catalog,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onItemClicked(QListWidgetItem*)));//当用户点击目录项时触发
    //提供媒体的总时长，通常在媒体加载完成后触发，用来显示媒体的总长度。
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(musicPlyerDurationChanged(qint64)));
    //提供当前播放进度，通常在媒体播放过程中持续触发，用来显示当前播放的时间或更新进度条。
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(musicPlyerPositionChanged(qint64)));
    connect(ui->horizontalSlider_schedule,SIGNAL(sliderReleased()),this,SLOT(durationSliderReleased()));//当用户释放进度条时
    connect(slider_Sound,&QSlider::sliderMoved,[=](int position){//当用户移动声音调节滑块时触发
        if(position == 99)
            position = 100;
        mediaPlayer->setVolume(position);
        label_Sound->clear();
        label_Sound->setText(QString::number(position));
        timer_Sound->start(3000);
    });
    connect(timer_Sound,&QTimer::timeout,[=](){//当定时器定时到时触发，隐藏控件
        timer_Sound->stop();
        slider_Sound->hide();
        label_Sound->hide();
    });
    connect(timer_catalog,&QTimer::timeout,[=](){//当定时器定时到触发，隐藏视频目录
        timer_catalog->stop();
        listWidget_catalog->hide();
    });
}

Video::~Video()
{
    delete ui;
}

void Video::hide__()
{
    listWidget_catalog->hide();//隐藏视频目录控件
    mediaPlayer->pause();//暂停视频播放
    hide();//隐藏当前控件（video）
}

//扫描视频文件
void Video::scanVideos()
{
    QDir dir(QCoreApplication::applicationDirPath() + "/myVideo");//视频文件存储路径
    QDir dirbsolutePath(dir.absolutePath());//绝对路径
    // 目录存在？
    if(!dirbsolutePath.exists())
    {
        qDebug()<<"Errpr number:";
        return;
    }

    video_Data.clear();
    listWidget_catalog->clear();

    QStringList filter; // 定义过滤器
    filter << "*.mp4" << "*.mkv" << "*.wmv" << "*.avi" << "*.mp3";
    // 获取目录下的文件
    QFileInfoList files = dirbsolutePath.entryInfoList(filter,QDir::Files);

    for(int i = 0; i< files.count(); i++)
    {
        // 使用utf-8
        QString fileName = QString::fromUtf8(files.at(i).fileName().toUtf8().data());//文件名
        QString filePath = QString::fromUtf8(files.at(i).filePath().toUtf8().data());//文件路径

        video_data info;
        item_number++;//数量+1
        info.fileName = QString::number(item_number)+ "." + fileName;//把文件名和文件路径放进自定义的信息结构体中
        info.filePath = QString::fromUtf8(files.at(i).filePath().toUtf8().data());

        // 媒体列表添加视频
        if(mediaPlayerList->addMedia(QUrl::fromLocalFile(filePath)))
        {
            // 添加到内容数组里储存
            video_Data.append(info);
            // 添加名字到列表
            listWidget_catalog->addItem(fileName);
        }
        else
        {
            qDebug()<<mediaPlayerList->errorString().toUtf8().data();
            qDebug()<<"Error number:"<<mediaPlayerList->error();
        }
    }
}


void Video::on_pushButton_volume_clicked()  // 音量按键
{
    slider_Sound->setGeometry(ui->pushButton_volume->x() + 10, this->height() - ui->widget_bool->height() - 120, ui->pushButton_volume->width() - 20,120);
    slider_Sound->raise();
    label_Sound->setGeometry(ui->pushButton_volume->x() - ui->pushButton_volume->width()/2, this->height() - ui->widget_bool->height(), ui->pushButton_volume->width(), ui->widget_bool->height());
    label_Sound->raise();
    if(slider_Sound->isVisible())
    {
        slider_Sound->hide();
        label_Sound->hide();
    }
    else
    {
        slider_Sound->show();
        label_Sound->show();
        timer_Sound->start(3000);//开启定时器，时间到后自动隐藏
    }
}

void Video::on_pushButton_menu_clicked()  // 目录按键
{
    if(listWidget_catalog->isVisible())
        listWidget_catalog->hide();
    else
    {
        scanVideos();
        listWidget_catalog->show();//显示目录
        timer_catalog->start(4000);
    }
}

void Video::on_pushButton_switch_clicked()  // 播放停止按键
{
    if(mediaPlayer->state() == QMediaPlayer::PausedState || mediaPlayer->state() == QMediaPlayer::StoppedState)  // 当前是停止状态，则要播放
    {
        ui->pushButton_switch->setStyleSheet("QPushButton{border-image: url(:/images/video_pic/btn_pause1.png)}");//切换按钮的样子
        mediaPlayer->play();//播放
    }
    else if(mediaPlayer->state() == QMediaPlayer::PlayingState)   // 播放状态
    {
        ui->pushButton_switch->setStyleSheet("QPushButton{border-image: url(:/images/video_pic/btn_play1.png)}");
        mediaPlayer->pause();
    }
}

void Video::on_pushButton_next_clicked()  // 播放下一个视频
{
    mediaPlayer->stop();
    int count = mediaPlayerList->mediaCount();
    if(0 == count)
        return;
    mediaPlayerList->next();
    mediaPlayer->play();
}

//当视频目录中的某一项被点击时触发
void Video::onItemClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)
    mediaPlayer->stop();//暂停当前播放
    QString amount = item->text().split(".").at(0);//获取点击项的序号（没用到，估计是作者后来改了）
    mediaPlayerList->setCurrentIndex(listWidget_catalog->row(item)-1);//设置索引为被点击项
    //musicPlyer->setMedia(QUrl::fromLocalFile(music_Data[amount.toInt() - 1].filePath));//
    mediaPlayer->play();//播放
    //ui->label_name->setText((music_Data[amount.toInt() - 1].fileName.split(".").at(1)).split(" ").at(0));
    ui->pushButton_switch->setStyleSheet("QPushButton{border-image: url(:/images/video_pic/btn_pause1.png)}");
}

//提供媒体的总时长，通常在媒体加载完成后触发，用来显示媒体的总长度。
void Video::musicPlyerDurationChanged(qint64 duration)
{
    ui->horizontalSlider_schedule->setRange(0 , duration / 1000);//获得视频总时长，然后设置滚动条的范围
    int second = duration / 1000; // 全部秒
    int minute = second / 60;     // 分钟
    second %= 60;                 // 秒

    QString mediDuration;
    mediDuration.clear();

    if(minute >= 10)
        mediDuration = QString::number(minute,10);
    else
        mediDuration = "0" + QString::number(minute,10);

    if(second >= 10)
        mediDuration = mediDuration + ":" + QString::number(second,10);
    else
        mediDuration = mediDuration + ":0" + QString::number(second,10);

    maxtime = mediDuration;
}

////提供当前播放进度，通常在媒体播放过程中持续触发，用来显示当前播放的时间或更新进度条。
void Video::musicPlyerPositionChanged(qint64 position)
{
    if(!ui->horizontalSlider_schedule->isSliderDown())// 不是手动调节进度条
        ui->horizontalSlider_schedule->setValue(position/1000);

    int second = position / 1000; // 秒
    int minute = second / 60;     // 分钟
    //int64_t second_miao = position / 10;
    second %= 60;

    // 实时播放时间
    QString mediPosition;
    mediPosition.clear();

    if(minute >= 10)
        mediPosition = QString::number(minute,10);
    else
        mediPosition = "0" + QString::number(minute,10);

    if(second >= 10)
        mediPosition = mediPosition + ":" + QString::number(second,10);
    else
        mediPosition = mediPosition + ":0" + QString::number(second,10);

    ui->label_time->setText(mediPosition + "/" + maxtime);
}

//用户手动拖动进度条然后释放时触发
void Video::durationSliderReleased()
{
    mediaPlayer->setPosition(ui->horizontalSlider_schedule->value() * 1000);
}
