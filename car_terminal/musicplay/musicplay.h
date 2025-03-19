#ifndef MUSICPLAY_H
#define MUSICPLAY_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QSlider>
#include <QTimer>

#include <QDebug>
#include "lyric.h"

/*************音乐**************/

struct music_data{
    QString fileName;      // 歌曲文件名
    QString filePath;      // 歌曲文件路径
    QString fileLinesPath; // 歌词文件路径
};

QT_BEGIN_NAMESPACE
namespace Ui { class MusicPlay; }
QT_END_NAMESPACE

class MusicPlay : public QWidget
{
    Q_OBJECT

public:
    MusicPlay(QWidget *parent = nullptr);
    ~MusicPlay();

private slots:

    void on_pushButton_page_clicked();

    void on_pushButton_pattern_clicked();

    void on_pushButton_play_clicked();

private:
    void in_it();
    void scanSongs();

private slots:
    void onItemDoubleClicked(QListWidgetItem *);

    void on_pushButton_under_clicked();

    void on_pushButton_on_clicked();

    void mediaPlylistCurrentIndexChanged(int);

    void musicPlyerDurationChanged(qint64); // 总时长

    void musicPlyerPositionChanged(qint64); // 当前播放了的时长

    void musicPlyerStateChanged(QMediaPlayer::State); // 播放状态改变

    void durationSliderReleased();          // 设置播放时间跟随滑动条

    void on_volume_clicked();

    void alter_lyric(qint64);

private:
    Ui::MusicPlay *ui;
    QVector<music_data> music_Data;      // 媒体信息存储
    QMediaPlayer *musicPlyer;            // 媒体播放器，用于播放音乐
    QMediaPlaylist *mediaPlylist;        // 媒体列表
    QListWidget *listwidget_lyric;       // 歌词列表
    QListWidget *listwidget_songlist;    // 歌单列表
    QSlider *slider_Sound;               // 声音调节
    QTimer *timer_Sound;
    Lyric *lyric;                        // 歌词类
    bool page;
    int pattern;
    int item;
};
#endif // MUSICPLAY_H
