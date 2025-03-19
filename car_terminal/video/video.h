#ifndef VIDEO_H
#define VIDEO_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <QDebug>

#include <QVideoWidget>  // 控件
#include <QListWidget>
#include <QSlider>
#include <QLabel>
//#include "video/mylistwidget_.h"
#include "folder/mylistwidget.h"

/*************视频**************/

struct video_data{
    QString fileName;      // 视频文件名
    QString filePath;      // 视频文件路径
};

QT_BEGIN_NAMESPACE
namespace Ui { class Video; }
QT_END_NAMESPACE

class Video : public QWidget
{
    Q_OBJECT

public:
    Video(QWidget *parent = nullptr);
    ~Video();

    void hide__();
private slots:
    void on_pushButton_volume_clicked();

    void on_pushButton_menu_clicked();

    void on_pushButton_switch_clicked();

    void on_pushButton_next_clicked();

    void onItemClicked(QListWidgetItem *);  // 单机

    void musicPlyerDurationChanged(qint64); // 总时长

    void musicPlyerPositionChanged(qint64); // 当前播放了的时长

    void durationSliderReleased();          // 设置播放时间跟随滑动条

private:
    void scanVideos();

private:
    Ui::Video *ui;
    QVector<video_data> video_Data;    // 视频容器
    QVideoWidget *videoWidget;         // 视频显示组件窗口
    QMediaPlayer *mediaPlayer;         // 媒体播放器
    QMediaPlaylist * mediaPlayerList;
    MyListWidget *listWidget_catalog;
    QSlider *slider_Sound;
    QLabel *label_Sound;
    QTimer *timer_Sound;
    QTimer *timer_catalog;
    int item_number;
    QString maxtime;
};
#endif // VIDEO_H
