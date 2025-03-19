#ifndef WFORECAST_H
#define WFORECAST_H

#include <QWidget>
// 网络
#include <QApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
// json解析
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPaintEvent>
#include <QPainter>

//#include <QTimer>

class WForecast : public QWidget
{
    Q_OBJECT
public:
     WForecast(QWidget *parent = nullptr,QString city = "呼和浩特");
     ~WForecast();

     void get_new_Weather(QString);
     void get_Weather();

private slots:
     void json_weather(QNetworkReply*);

signals:
     void data_updating();
     void data_lose(bool);

public:
     //存数据
     QString city;
     QString wind_type[5];         // 风
     QString arm_type[5];          // 天气
     QString date_type[5];         // 日期
     QString temperature_type[5];  // 温度
     QString humidity;             // 湿度
     QString AQI;                  // 空气指数
     QString wind_scale;           // 风力等级
     QString temperature_present;  // 当前温度
     QString arm_present;          // 当前天气
     QString reson;                // 网络获取状态（成功？）

private:
     QNetworkAccessManager *request_weather;
     QString weather_api = "http://apis.juhe.cn/simpleWeather/query?city=%1&key=251518e073ef6c3c9504dd286c3f6a86";
     QString city_1;               // 输入城市

};

#endif // WFORECAST_H
