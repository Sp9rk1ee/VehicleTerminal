#ifndef USE_H
#define USE_H

#include <QWidget>
#include <QDebug>
#include <myMap/mymap.h>
#include <musicplay/musicplay.h>
#include <video/video.h>

// 定义一个use类，和tool那边类似

namespace Ui {
class Use;
}

class Use : public QWidget
{
    Q_OBJECT

public:
    explicit Use(QWidget *parent = nullptr,QWidget *parent1 = nullptr);
    ~Use();

    void useName(bool);
    void wifi_judge(bool);       //  获取wifi是否可以使用
    void hide_all();

private slots:
    void on_pushButton_video_clicked();

    void on_pushButton_music_clicked();

    void on_pushButton_browser_clicked();

    void on_pushButton_weather_clicked();

    void on_pushButton_map_clicked();

    void on_pushButton_radio_clicked();

signals:
    void weather_show();
    void hide_show_use();

private:
    Ui::Use *ui;
    MyMap *mymap;
    MusicPlay *musicPlay;
    Video *video;
    QWidget *use_ui;
    bool wifi_judge_;
};

#endif // USE_H
