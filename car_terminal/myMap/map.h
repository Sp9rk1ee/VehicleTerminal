#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>  // 网络入口
#include <QtNetwork/QNetworkReply>          // 回答
#include <QtNetwork/QNetworkRequest>        // 请求

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>


class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

    void get_map(double longitude,double latitude,int zoom);

private:
    void get_image(QNetworkReply *reply);

signals:
    void map_image(QImage*);  // 地图图片

private:
    const QString server_aip = "http://api.tianditu.gov.cn/staticimage?center=%1,%2&width=1100&height=600&zoom=%3&layers= vec_c,cva_c&markers=%4,%5&tk=cd7c72446ffb4f934236ed82e3faf18e";
    QNetworkAccessManager *networkAccessManager;
    int zoom;
};

#endif // MAP_H
