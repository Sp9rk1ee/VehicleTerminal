#ifndef LONGITUDELATITUDE_H
#define LONGITUDELATITUDE_H


// 经纬度获取
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>  // 网络入口
#include <QtNetwork/QNetworkReply>          // 回答
#include <QtNetwork/QNetworkRequest>        // 请求

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

struct iste_data
{
    QString lonlat;
    QString phone;
    QString address;
    QString name;
};

class LongitudeLatitude : public QObject
{
    Q_OBJECT
public:
    explicit LongitudeLatitude(QObject *parent = nullptr);
    ~LongitudeLatitude();

    void get_LongitudeLatitude(QString city);

private:
    void get_JsonValue(QNetworkReply *reply);

signals:
    void lonlat(double longitude,double latitude);  // 经度

public:
    QVector<iste_data> iste_Data;  // 地址数据 容器

private:
    const QString server_aip = "http://api.tianditu.gov.cn/v2/search?postStr={\"keyWord\":\"%1\",\"level\":12,\"mapBound\":\"116.02524,39.83833,116.65592,39.99185\",\"queryType\":1,\"start\":0,\"count\":10}&type=query&tk=cd7c72446ffb4f934236ed82e3faf18e";
    QNetworkAccessManager *networkAccessManager;

};
#endif // LONGITUDELATITUDE_H
