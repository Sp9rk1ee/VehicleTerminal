#include "musicplay.h"
#include "ui_musicplay.h"

#include <QFile>
#include <QFileInfoList>
#include <QDir>
#include <QCoreApplication>
//#include <QProcess>

#include <QFileDialog>

MusicPlay::MusicPlay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MusicPlay)
{
    ui->setupUi(this);

    in_it();

}

MusicPlay::~MusicPlay()
{
    delete ui;
}

void MusicPlay::in_it()
{
    // 背景
//    QPalette pal = this->palette();
//    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/video_pic/bg.png")));
//    setPalette(pal);

    musicPlyer = new QMediaPlayer(this);//QMediaPlayer 是 Qt 中用来播放音频和视频文件的类。
    mediaPlylist = new QMediaPlaylist(this);//QMediaPlaylist 用于管理一组媒体文件，允许设置播放顺序和控制播放列表。
    mediaPlylist->clear();   // 列表为空
    musicPlyer->setPlaylist(mediaPlylist);  // 设置音乐播放列表为mediaPlaylist
    mediaPlylist->setPlaybackMode(QMediaPlaylist::Sequential);  // 设置播放模式，为俺顺序播放
    musicPlyer->setVolume(50);//设置音量为50

    // 声音调节控件
    slider_Sound = new QSlider(Qt::Vertical,this);//创建一个滚动条，用于控制音量
    slider_Sound->setValue(50);//设置滚动条的值
    slider_Sound->setStyleSheet("border-image: url(:/images/music_pic/sub-page1.png);");//设置滚动条样式
    slider_Sound->hide();//隐藏滚动条
    timer_Sound = new QTimer(this);//创建定时器

    // 歌词
    lyric= new Lyric(this);//实例化一个歌词类（自定义的）

    // listWidget
    listwidget_lyric = new QListWidget(ui->listWidget);//QListWidget 是一个用于显示列表项的控件，在此上下文中，它将用来显示歌词
    listwidget_lyric->setStyleSheet("font-size:20px;color: rgb(100, 100, 100);");//设置样式
    listwidget_lyric->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    // 隐藏滚动条（水平）
    listwidget_lyric->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);      // 隐藏滚动条（垂直）
    listwidget_lyric->addItem("  歌 词");//添加一项，内容为歌词
    listwidget_lyric->addItem("");
    listwidget_lyric->addItem("");
    listwidget_lyric->addItem("");
    listwidget_lyric->addItem("");
    listwidget_lyric->addItem("");
    listwidget_lyric->addItem("");
    listwidget_lyric->addItem("");
    listwidget_lyric->addItem("");
    listwidget_lyric->item(1)->setForeground(Qt::green);                       // 设置第一项的颜色，也就是播放行颜色
    listwidget_songlist = new QListWidget(ui->listWidget);      //歌曲列表
    listwidget_songlist->setStyleSheet("font-size:20px;color: rgb(100, 100, 100);");
    listwidget_songlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 隐藏滚动条（水平）
    listwidget_songlist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // 隐藏滚动条（垂直）
    listwidget_songlist->addItem("  歌 单");
    listwidget_lyric->setFixedSize(QSize(312,266));//设置大小
    listwidget_songlist->setFixedSize(QSize(312,266));
    listwidget_lyric->hide();
    listwidget_songlist->show();
    page = false;  // 歌词/歌单
    pattern = 0;   // 播放模式
    item = 0;      // 项数

    scanSongs();//扫描歌曲
//    QIcon icon_init[9];
//    icon_init[0].addFile("://images/music_pic/btn_previous1.png");
//    ui->pushButton_on->setStyleSheet("QPushButton{border-image: url(:/images/music_pic/btn_next1.png)}");
    connect(listwidget_songlist,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onItemDoubleClicked(QListWidgetItem*)));
    connect(listwidget_lyric,SIGNAL(currentRowChanged(int)),this,SLOT(mediaPlylistCurrentIndexChanged(int)));
    connect(musicPlyer,SIGNAL(durationChanged(qint64)),this,SLOT(musicPlyerDurationChanged(qint64)));
    connect(musicPlyer,SIGNAL(positionChanged(qint64)),this,SLOT(musicPlyerPositionChanged(qint64)));
    connect(musicPlyer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(musicPlyerStateChanged(QMediaPlayer::State)));
    connect(ui->horizontalSlider_duration,SIGNAL(sliderReleased()),this,SLOT(durationSliderReleased()));
    connect(lyric,SIGNAL(Line_alter(qint64)),this,SLOT(alter_lyric(qint64)));
    connect(slider_Sound,&QSlider::sliderMoved,[=](int position){
        musicPlyer->setVolume(position);
        timer_Sound->start(3000);
    });
    connect(timer_Sound,&QTimer::timeout,[=](){
        timer_Sound->stop();
        //slider_Sound->hide();
    });
}

void MusicPlay::scanSongs()
{
    QDir dir(QCoreApplication::applicationDirPath() + "/myMusic");//获得音乐所在的路径
    QDir dirbsolutePath(dir.absolutePath());//返回dir的绝对路径
    //qDebug()<<QCoreApplication::applicationDirPath();
    // 目录存在？
    if(!dirbsolutePath.exists())
    {
        qDebug()<<"歌曲文件夹目录不存在";
        return;
    }

    QStringList filter; // 定义过滤器
    filter << "*.mp3";
    // 获取目录下的文件
    QFileInfoList files = dirbsolutePath.entryInfoList(filter,QDir::Files);//获取目录下所有符合条件的文件（即 .mp3 文件）。

    for(int i = 0; i< files.count(); i++)//遍历所有mp3文件
    {
        music_data info;
        // 使用utf-8
        QString fileNme = QString::fromUtf8(files.at(i).fileName().replace(".mp3","").toUtf8().data());//文件名去掉MP3后缀
        QString kongwei;
        for (int i = 0; i < (20-fileNme.size()); ++i) {//占位符
            kongwei = kongwei + " ";
        }
        item++;
        info.fileName = QString::number(item)+ "." + fileNme + kongwei + fileNme.split("-").at(1);//文件名
        info.filePath = QString::fromUtf8(files.at(i).filePath().toUtf8().data());//歌曲路径
        info.fileLinesPath = info.filePath.split(".").at(0) + ".lrc";//歌词路径
        //qDebug()<<info.fileLinesPath<<info.filePath;

        // 媒体列表添加歌曲
        if(mediaPlylist->addMedia(QUrl::fromLocalFile(info.filePath)))//把歌曲添加到媒体播放列表
        {
            // 添加到内容数组里储存
            music_Data.append(info);
            // 添加歌曲名字到歌单列表
            listwidget_songlist->addItem(info.fileName);
        }
        else
        {
            qDebug()<<mediaPlylist->errorString().toUtf8().data();
            qDebug()<<"Error number:"<<mediaPlylist->error();
        }
    }


}


void MusicPlay::onItemDoubleClicked(QListWidgetItem * item) // 双击
{
    Q_UNUSED(item)
    musicPlyer->stop();//停止当前正在播放的音乐
    QString amount = item->text().split(".").at(0);//获取双击的 QListWidgetItem 对应的文本（歌曲名）
    mediaPlylist->setCurrentIndex(listwidget_songlist->row(item)-1);//设置当前播放列表索引
    //musicPlyer->setMedia(QUrl::fromLocalFile(music_Data[amount.toInt() - 1].filePath));//
    musicPlyer->play();//播放音乐
    ui->label_name->setText((music_Data[amount.toInt() - 1].fileName.split(".").at(1)).split(" ").at(0));//更新界面显示的歌曲名称
    ui->pushButton_play->setStyleSheet("QPushButton{border-image: url(:/images/music_pic/btn_pause1.png)}");//更新播放按钮样式
}


void MusicPlay::on_pushButton_page_clicked()
{
    if(page) // 歌单   如果 page 为 true，表示当前显示的是歌词（listwidget_lyric,切换
    {
        listwidget_lyric->hide();
        listwidget_songlist->show();
        page = false;
    }
    else     // 歌词
    {
        scanSongs();
        listwidget_lyric->show();
        listwidget_songlist->hide();
        page = true;
    }
}



void MusicPlay::on_pushButton_pattern_clicked()
{
    if(pattern == 0)      // 随机
    {
        mediaPlylist->setPlaybackMode(QMediaPlaylist::Random);
        ui->pushButton_pattern->setStyleSheet("QPushButton{border-image: url(:/images/music_pic/btn_listrandom.png)}");
        pattern = 1;
    }
    else if(pattern == 1) // 循环
    {
        mediaPlylist->setPlaybackMode(QMediaPlaylist::Loop);
        ui->pushButton_pattern->setStyleSheet("QPushButton{border-image: url(:/images/music_pic/btn_listjump.png)}");
        pattern = 2;
    }
    else                  // 顺序
    {
        mediaPlylist->setPlaybackMode(QMediaPlaylist::Sequential);
        ui->pushButton_pattern->setStyleSheet("QPushButton{border-image: url(:/images/music_pic/btn_listsingle.png)}");
        pattern = 0;
    }
}


void MusicPlay::on_pushButton_play_clicked()
{
    if(musicPlyer->state() == QMediaPlayer::PausedState)// 播放
    {
        ui->pushButton_play->setStyleSheet("QPushButton{border-image: url(:/images/music_pic/btn_pause1.png)}");
        musicPlyer->play();
    }
    else if(musicPlyer->state() == QMediaPlayer::PlayingState)   // 停止
    {
        ui->pushButton_play->setStyleSheet("QPushButton{border-image: url(:/images/music_pic/btn_play1.png)}");
        musicPlyer->pause();
    }
}

// 切换下一首歌曲播放
void MusicPlay::on_pushButton_under_clicked()
{
    musicPlyer->stop();
    int count = mediaPlylist->mediaCount();
    if(0 == count)
        return;

    mediaPlylist->next();
    musicPlyer->play();
    int music_now_number = mediaPlylist->currentIndex();
    if(music_now_number == -1)//返回当前播放的歌曲索引。如果返回值是 -1（表示没有当前歌曲），则将 music_now_number 设置为播放列表中的最后一首歌曲的索引
        music_now_number = mediaPlylist->mediaCount()-1;
    ui->label_name->setText(music_Data[music_now_number].fileName.split(".").at(1).split(" ").at(0));//更新显示的歌曲名称
}

//播放上一首
void MusicPlay::on_pushButton_on_clicked()
{
//    qDebug()<<"左";  // 添加歌曲文件
//    QString filter="音频文件(*.mp3 *.wav *.wma)mp3文件(*.mp3);;wav文件(*.wav);;wma文件(*.wma);;所有文件(*.*)";
//           QStringList fileList = QFileDialog::getOpenFileNames(this,"选择音频文件","D:",filter);
//              for(auto i=0; i<fileList.count(); ++i)
//               {
//                  QString path=fileList.at(i);
//                  mediaPlylist->addMedia(QUrl::fromLocalFile(path));
//                  //QString fileName=path.split("/").last();
//                  listwidget_songlist->addItem(path);
//                  //insertSql(fileList.at(i));
//               }

    musicPlyer->stop();
    //mediaPlylist->mediaCount() 返回播放列表中的歌曲数量。如果播放列表为空（count == 0），则直接返回，不执行后续的操作。
    int count = mediaPlylist->mediaCount();
    if(0 == count)
        return;

    mediaPlylist->previous();//切换到上一首歌曲
    musicPlyer->play();//播放上一首
    int music_now_number = 8;
            music_now_number = mediaPlylist->currentIndex();//返回当前播放的歌曲的索引
    if(music_now_number == -1)//如果当前歌曲索引无效（-1），则设置为最后一首歌
        music_now_number = mediaPlylist->mediaCount()-1;
    ui->label_name->setText(music_Data[music_now_number].fileName.split(".").at(1).split(" ").at(0));//更新显示的歌曲名称
}

//当播放列表中的当前歌曲（即索引）发生变化时，这个函数会被触发
void MusicPlay::mediaPlylistCurrentIndexChanged(int index)
{
    if(-1 == index)
        return;
    // 设置列表正在播放的项
    listwidget_lyric->setCurrentRow(index);
}

//当播放器开始播放，会触发这个函数。
//这个函数的作用是计算并格式化音频/视频文件的总时长（以分钟和秒为单位），并将其显示在界面上的 label_time_over 标签中。
void MusicPlay::musicPlyerDurationChanged(qint64 duration)
{
    ui->horizontalSlider_duration->setRange(0 , duration / 1000);
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

    ui->label_time_over->setText(mediDuration);
}

//当播放器的当前位置发生变化时（即播放进度发生变化时），会触发这个函数。
//这个函数的作用是根据当前播放位置更新进度条、实时显示播放时间（以分钟和秒为单位）并更新歌词显示。
void MusicPlay::musicPlyerPositionChanged(qint64 position)
{
    if(!ui->horizontalSlider_duration->isSliderDown())// 不是手动调节进度条
        ui->horizontalSlider_duration->setValue(position/1000);

    int second = position / 1000; // 秒
    int minute = second / 60;     // 分钟
    int64_t second_miao = position / 10;
    second %= 60;

    // 歌词文本更新
    lyric->lyric_Line(second_miao);

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

    ui->label_time_real->setText(mediPosition);
}

//这个槽函数的作用是当播放器进入播放状态时（QMediaPlayer::PlayingState），执行一些操作来更新歌词显示。
void MusicPlay::musicPlyerStateChanged(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::PlayingState)  // 播放状态
    {   //这行代码判断当前播放进度是否处于音频文件的开头部分（前20ms）。如果是，则执行以下操作，确保在播放开始时加载并显示歌词。
        if(musicPlyer->position() <= 20)
        {   //这部分代码获取当前播放列表中正在播放的媒体的索引。如果当前索引是 -1 或 -2，则认为当前歌曲是列表中的最后一首。
            int music_now_number = mediaPlylist->currentIndex();
            if(music_now_number == -2 || music_now_number == -1)
                music_now_number = mediaPlylist->mediaCount() - 1;
            lyric->lyric_Binding(music_Data[music_now_number].fileLinesPath);//通过 lyric->lyric_Binding 函数加载当前歌曲的歌词文件
            //qint64 now_lyric = lyric->lyric_Line(musicPlyer->position());
            if(lyric->lyric_Data.size())
            {   //这段代码检查 lyric->lyric_Data 中是否存在歌词数据。如果存在，则通过 setText() 方法将歌词逐项显示在 listwidget_lyric 中
                listwidget_lyric->item(1)->setText(lyric->lyric_Data[0].text_lyric);
                listwidget_lyric->item(2)->setText(lyric->lyric_Data[1].text_lyric);
                listwidget_lyric->item(3)->setText(lyric->lyric_Data[2].text_lyric);
                listwidget_lyric->item(4)->setText(lyric->lyric_Data[3].text_lyric);
                listwidget_lyric->item(5)->setText(lyric->lyric_Data[4].text_lyric);
                listwidget_lyric->item(6)->setText(lyric->lyric_Data[5].text_lyric);
                listwidget_lyric->item(7)->setText(lyric->lyric_Data[6].text_lyric);
                listwidget_lyric->item(8)->setText(lyric->lyric_Data[7].text_lyric);
            }

        }
    }
}
//在用户停止拖动进度条时触发
void MusicPlay::durationSliderReleased()
{
    /* 设置媒体播放的位置 */
    musicPlyer->setPosition(ui->horizontalSlider_duration->value() * 1000);
}

//点击音量按钮时触发，音量滑块会在按钮上方显示或隐藏
void MusicPlay::on_volume_clicked()  // 音量
{
    slider_Sound->setGeometry(ui->volume->x(),ui->volume->y() - 100,ui->volume->width(),100);//设置音量滑块的位置和大小
    slider_Sound->raise();//将音量滑块提升到最上层，这样它就不会被其他控件遮挡。
    if(slider_Sound->isVisible())//如果滑块已经可见，调用 slider_Sound->hide() 隐藏它。
        slider_Sound->hide();
    else
    {   //如果滑块不可见，调用 slider_Sound->show() 显示它，并启动一个定时器
        slider_Sound->show();
        timer_Sound->start(3000);
    }
}

//用于更新显示当前歌词的界面。具体来说，它根据传入的 number_lyric_line 值（表示当前显示的歌词行号）
void MusicPlay::alter_lyric(qint64 number_lyric_line)
{
    number_lyric_line = number_lyric_line - 1;
    int lyric_size_Line = lyric->lyric_Data.size();//歌词总行数
    const int item_text7 = lyric_size_Line - 8;//示获取歌词数组中的倒数第八行
    const int item_text6 = lyric_size_Line - 7;
    const int item_text5 = lyric_size_Line - 6;
    const int item_text4 = lyric_size_Line - 5;
    const int item_text3 = lyric_size_Line - 4;
    const int item_text2 = lyric_size_Line - 3;
    const int item_text1 = lyric_size_Line - 2;
    const int item_text0 = lyric_size_Line - 1;

    //以下的好几个if主要是对歌曲唱到最后几行时进行特殊处理
    if(item_text7 == number_lyric_line)//如果 number_lyric_line 的值等于 item_text7（即当前歌词的行号是倒数第八行
    {
        //将 number_lyric_line 对应的歌词文本（即 lyric_Data[number_lyric_line].text_lyric）设置为列表项 1 的文本。
        listwidget_lyric->item(1)->setText(lyric->lyric_Data[number_lyric_line].text_lyric);
        listwidget_lyric->item(2)->setText(lyric->lyric_Data[number_lyric_line + 1].text_lyric);
        listwidget_lyric->item(3)->setText(lyric->lyric_Data[number_lyric_line + 2].text_lyric);
        listwidget_lyric->item(4)->setText(lyric->lyric_Data[number_lyric_line + 3].text_lyric);
        listwidget_lyric->item(5)->setText(lyric->lyric_Data[number_lyric_line + 4].text_lyric);
        listwidget_lyric->item(6)->setText(lyric->lyric_Data[number_lyric_line + 5].text_lyric);
        listwidget_lyric->item(7)->setText(lyric->lyric_Data[number_lyric_line + 6].text_lyric);
        listwidget_lyric->item(8)->setText(" ");
    }
    else if(item_text6 == number_lyric_line)
    {
        listwidget_lyric->item(1)->setText(lyric->lyric_Data[number_lyric_line].text_lyric);
        listwidget_lyric->item(2)->setText(lyric->lyric_Data[number_lyric_line + 1].text_lyric);
        listwidget_lyric->item(3)->setText(lyric->lyric_Data[number_lyric_line + 2].text_lyric);
        listwidget_lyric->item(4)->setText(lyric->lyric_Data[number_lyric_line + 3].text_lyric);
        listwidget_lyric->item(5)->setText(lyric->lyric_Data[number_lyric_line + 4].text_lyric);
        listwidget_lyric->item(6)->setText(lyric->lyric_Data[number_lyric_line + 5].text_lyric);
        listwidget_lyric->item(7)->setText(" ");
        listwidget_lyric->item(8)->setText(" ");
    }
    else if(item_text5 == number_lyric_line)
    {
        listwidget_lyric->item(1)->setText(lyric->lyric_Data[number_lyric_line].text_lyric);
        listwidget_lyric->item(2)->setText(lyric->lyric_Data[number_lyric_line + 1].text_lyric);
        listwidget_lyric->item(3)->setText(lyric->lyric_Data[number_lyric_line + 2].text_lyric);
        listwidget_lyric->item(4)->setText(lyric->lyric_Data[number_lyric_line + 3].text_lyric);
        listwidget_lyric->item(5)->setText(lyric->lyric_Data[number_lyric_line + 4].text_lyric);
        listwidget_lyric->item(6)->setText(" ");
        listwidget_lyric->item(7)->setText(" ");
        listwidget_lyric->item(8)->setText(" ");
    }
    else if(item_text4 == number_lyric_line)
    {
        listwidget_lyric->item(1)->setText(lyric->lyric_Data[number_lyric_line].text_lyric);
        listwidget_lyric->item(2)->setText(lyric->lyric_Data[number_lyric_line + 1].text_lyric);
        listwidget_lyric->item(3)->setText(lyric->lyric_Data[number_lyric_line + 2].text_lyric);
        listwidget_lyric->item(4)->setText(lyric->lyric_Data[number_lyric_line + 3].text_lyric);
        listwidget_lyric->item(5)->setText(" ");
        listwidget_lyric->item(6)->setText(" ");
        listwidget_lyric->item(7)->setText(" ");
        listwidget_lyric->item(8)->setText(" ");
    }
    else if(item_text3 == number_lyric_line)
    {
        listwidget_lyric->item(1)->setText(lyric->lyric_Data[number_lyric_line].text_lyric);
        listwidget_lyric->item(2)->setText(lyric->lyric_Data[number_lyric_line + 1].text_lyric);
        listwidget_lyric->item(3)->setText(lyric->lyric_Data[number_lyric_line + 2].text_lyric);
        listwidget_lyric->item(4)->setText(" ");
        listwidget_lyric->item(5)->setText(" ");
        listwidget_lyric->item(6)->setText(" ");
        listwidget_lyric->item(7)->setText(" ");
        listwidget_lyric->item(8)->setText(" ");
    }
    else if(item_text2 == number_lyric_line)
    {
        listwidget_lyric->item(1)->setText(lyric->lyric_Data[number_lyric_line].text_lyric);
        listwidget_lyric->item(2)->setText(lyric->lyric_Data[number_lyric_line + 1].text_lyric);
        listwidget_lyric->item(3)->setText(" ");
        listwidget_lyric->item(4)->setText(" ");
        listwidget_lyric->item(5)->setText(" ");
        listwidget_lyric->item(6)->setText(" ");
        listwidget_lyric->item(7)->setText(" ");
        listwidget_lyric->item(8)->setText(" ");
    }
    else if(item_text1 == number_lyric_line)
    {
        listwidget_lyric->item(1)->setText(lyric->lyric_Data[number_lyric_line].text_lyric);
        listwidget_lyric->item(2)->setText(" ");
        listwidget_lyric->item(3)->setText(" ");
        listwidget_lyric->item(4)->setText(" ");
        listwidget_lyric->item(5)->setText(" ");
        listwidget_lyric->item(6)->setText(" ");
        listwidget_lyric->item(7)->setText(" ");
        listwidget_lyric->item(8)->setText(" ");
    }
    else if(item_text0 == number_lyric_line)
    {
        listwidget_lyric->item(1)->setText(" ");
        listwidget_lyric->item(2)->setText(" ");
        listwidget_lyric->item(3)->setText(" ");
        listwidget_lyric->item(4)->setText(" ");
        listwidget_lyric->item(5)->setText(" ");
        listwidget_lyric->item(6)->setText(" ");
        listwidget_lyric->item(7)->setText(" ");
        listwidget_lyric->item(8)->setText(" ");
    }
    else//如果不是最后八行歌词，那就正常显示
    {
        listwidget_lyric->item(1)->setText(lyric->lyric_Data[number_lyric_line].text_lyric);
        listwidget_lyric->item(2)->setText(lyric->lyric_Data[number_lyric_line + 1].text_lyric);
        listwidget_lyric->item(3)->setText(lyric->lyric_Data[number_lyric_line + 2].text_lyric);
        listwidget_lyric->item(4)->setText(lyric->lyric_Data[number_lyric_line + 3].text_lyric);
        listwidget_lyric->item(5)->setText(lyric->lyric_Data[number_lyric_line + 4].text_lyric);
        listwidget_lyric->item(6)->setText(lyric->lyric_Data[number_lyric_line + 5].text_lyric);
        listwidget_lyric->item(7)->setText(lyric->lyric_Data[number_lyric_line + 6].text_lyric);
        listwidget_lyric->item(8)->setText(lyric->lyric_Data[number_lyric_line + 7].text_lyric);
    }
}
