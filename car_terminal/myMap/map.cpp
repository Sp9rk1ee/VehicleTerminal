#include "map.h"

Map::Map(QWidget *parent) : QWidget(parent)
{
    networkAccessManager = new QNetworkAccessManager(this);////Qt 提供的 HTTP 网络请求管理器，用于 发送 HTTP 请求和接收服务器响应。

    connect(networkAccessManager,&QNetworkAccessManager::finished,this,&Map::get_image);
}

Map::~Map()
{
}
//get_map 函数的目的是通过网络请求来获取某个位置的地图数据。
//它使用传入的经纬度 (longitude 和 latitude) 和缩放级别 (zoom) 来构建一个 URL，
//然后通过 networkAccessManager 发送 GET 请求，通常这样的请求会从一个地图服务
void Map::get_map(double longitude,double latitude,int zoom)
{
    QNetworkRequest request;
    request.setUrl(QUrl(server_aip.arg(longitude).arg(latitude).arg(zoom).arg(longitude).arg(latitude)));
    networkAccessManager->get(request);
}

void Map::get_image(QNetworkReply *reply)
{
    QImage* image = new QImage();//QImage 是 Qt 中用于处理图像的类
    image->loadFromData(reply->readAll());//这行代码从网络请求的回复中读取所有数据，并将其加载到 image 对象中。
    if(image->isNull())
        qDebug()<<"oops";
    emit map_image(image);//发射一个信号 map_image，并将加载的 image 作为参数
}
