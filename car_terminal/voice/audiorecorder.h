#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QWidget>

#include <QAudioRecorder>
#include <QAudioProbe>
#include <QAudioBuffer>

#include <QUrl>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

/*录制wav音频*/
class AudioRecorder : public QWidget
{
    Q_OBJECT
public:
    AudioRecorder(QWidget *parent = nullptr);
    ~AudioRecorder();

public slots:
    void startRecorder();               // 开始录音
    void stopRecorder();                // 停止录音
    void updateProgress(qint64);        // 更新录音时长
    void processBuffer(const QAudioBuffer&);  // 更新录音level

private:
    void clearAudioLevels();  // 清空录音level

    qreal getPeakValue(const QAudioFormat &format);               // 这个函数返回给定音频格式的最大可能采样值
    QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);  // 返回每个声音的音频级别
    template<class T>
    QVector<qreal> getBufferLevels(const T *buffer,int frames,int channels);

private:
    QAudioRecorder *m_audioRecorder = nullptr;  // 录音类
    QAudioProbe *m_probe = nullptr;             // 用于探测缓冲区level

    // 录音设置容器，保存录音设备的可用信息
    QList<QVariant>devicesVar;
    QList<QVariant>codecsVar;
    QList<QVariant>containersVar;
    QList<QVariant>sampleRateVar;
    QList<QVariant>channelsVar;
    QList<QVariant>qualityVar;
    QList<QVariant>bitratesVar;

};

#endif // AUDIORECORDER_H
