#ifndef VOICE_H
#define VOICE_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include "asr.h"
#include "audiorecorder.h"
#include <QDebug>

/*************语音识别功能**************/

QT_BEGIN_NAMESPACE
namespace Ui { class Voice; }
QT_END_NAMESPACE

class Voice : public QWidget
{
    Q_OBJECT

public:
    Voice(QWidget *parent = nullptr);
    ~Voice();

private:
    void mousePressEvent(QMouseEvent *event);    // 鼠标按下
    void mouseReleaseEvent(QMouseEvent *event);  // 鼠标松开

private slots:
    void onTimer1TimeOut();
    void onTimer2TimeOut();
    void onTimer3TimeOut();
    void onAsrReadyData(QString);

signals:
    void get_led(bool);
private:
    Ui::Voice *ui;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;

    AudioRecorder *myAudioRecorder;  // 录音类
    Asr *myAsr;                      // 识别
};
#endif // VOICE_H
