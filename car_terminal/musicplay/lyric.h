#ifndef LYRIC_H
#define LYRIC_H

#include <QObject>
#include <QFile>
#include <QDebug>

struct lyric_data{
    qint64 time_Lyric;     // 时间
    QString text_lyric;    // 文本
};

class Lyric : public QObject
{
    Q_OBJECT
public:
    explicit Lyric(QObject *parent = nullptr);
    ~Lyric();

    void lyric_Binding(QString fileLinesPath);  // 绑定歌词

    void lyric_Line(qint64 music_time);

    QVector<lyric_data> lyric_Data;  // 媒体信息存储

private:
    qint64 time_msec(QString watch_time);


    QString Line_now_data;

signals:
    void Line_alter(qint64);

};

#endif // LYRIC_H
