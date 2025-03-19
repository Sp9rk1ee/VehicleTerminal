#include "lyric.h"

Lyric::Lyric(QObject *parent) : QObject(parent)
{

}

Lyric::~Lyric()
{

}

//获取歌词
void Lyric::lyric_Binding(QString fileLinesPath)
{
    lyric_Data.clear();//清空已有的歌词数据
    QFile lyricFile(fileLinesPath);//打开歌词文件
    if(lyricFile.exists() && lyricFile.open(QIODevice::ReadOnly | QIODevice::Text))  // 判断文件存在，文件打开成功？以文本模式打开
    {
        int eNum = 0;
        while (!lyricFile.atEnd()) {//歌词还没读取到末尾
            QByteArray line = lyricFile.readLine();//每次读取一行歌词
            QString str(line);//将 QByteArray 转换为 QString
            eNum++;
            if(eNum > 5)//跳过前五行
            {
                lyric_data info;
                info.time_Lyric = time_msec(str.split("]").at(0));//解析时间
                info.text_lyric = str.split("]").at(1).trimmed();//解析歌词文本

                lyric_Data.append(info);  // 添加到内容数组
            }
        }
        lyricFile.close();
    }
    else
        qDebug()<<"没有歌词文件";
    lyricFile.close();
}

//根据当前音乐播放的时间 (music_time) 匹配并更新歌词行，并触发信号 Line_alter(line_number)，用于通知界面更新歌词显示。
void Lyric::lyric_Line(qint64 music_time)
{
    if(music_time <= 10)//如果 music_time <= 10 毫秒，直接返回，避免匹配太短的时间。
        return;
    for (int line_number = 0; line_number < lyric_Data.size(); ++line_number) {//遍历lytic_Data中存储的每一行歌词
        if(music_time <= lyric_Data[line_number].time_Lyric)//找到第一个大于当前时间的那行歌词
        {   //Line_now_data：当前正在播放的歌词
            if(Line_now_data != lyric_Data[line_number].text_lyric)//如果当前正在播放的歌词和line_number记录的不一样
                emit Line_alter(line_number);//触发 Line_alter(line_number) 信号，通知界面切换歌词。
            Line_now_data = lyric_Data[line_number].text_lyric;//把当前正在播放的歌词切换为line_number记录的那个歌词
            return;//直接返回
        }
    }
}

//转换时间用于记录，方便比较
qint64 Lyric::time_msec(QString watch_time)  // 格式[00:00.00
{
    int minute = watch_time.split(":").at(0).mid(1).toInt();
    double second =  watch_time.split(":").at(1).toDouble();
    //qDebug()<<minute<<second;
    return minute * 6000 + second * 100;
}
