#include "longitudelatitude.h"

LongitudeLatitude::LongitudeLatitude(QObject *parent) : QObject(parent)
{
    networkAccessManager = new QNetworkAccessManager(this);//Qt 提供的 HTTP 网络请求管理器，用于 发送 HTTP 请求和接收服务器响应。
    //网络请求完成时自动触发finished信号，调用槽函数用于接收和处理网络请求返回的数据
    connect(networkAccessManager,&QNetworkAccessManager::finished,this,&LongitudeLatitude::get_JsonValue);
}

LongitudeLatitude::~LongitudeLatitude()
{

}

//根据指定的城市名称发送网络请求请求城市的经纬度数据
void LongitudeLatitude::get_LongitudeLatitude(QString city)
{
    QNetworkRequest request;//创建一个网络请求对象
    request.setUrl(QUrl(server_aip.arg(city)));/// 设置请求的 URL，使用城市名称填充 `server_aip` 字符串中的占位符
    networkAccessManager->get(request);//// 发送 GET 请求
}

void LongitudeLatitude::get_JsonValue(QNetworkReply *reply)
{
    QString all = reply->readAll();//读取所有的响应数据
    //qDebug()<<all;
    QJsonParseError json_error;// 用于存储 JSON 解析过程中的错误信息
    QJsonDocument json_recv = QJsonDocument::fromJson(all.toUtf8(),&json_error);//解析 JSON 字符串
    QJsonObject json_object = json_recv.object();//将解析后的 JSON 文档转换为 JSON 对象:
    int reson = json_object.value("resultType").toInt();//提取 "resultType" 字段的值:

    switch (reson) {
    case 1:  // 普通POI
        iste_Data.clear(); //清空容器

        if(json_object.contains("pois"))//如果 json_object 中包含名为 "pois" 的字段，则继续处理。"pois" 字段包含了兴趣点（POI）数据
        {
            QJsonValue json_value = json_object.value("pois");//提取 "pois" 字段的值，返回的是一个 QJsonValue 对象，它可能是一个数组或对象。

            if(json_value.isArray())//检查 "pois" 字段是否为数组:
            {
                for (int i = 0; i < 10; ++i) {//遍历 "pois" 数组，处理每个 POI 数据:
                    iste_data info;//创建一个 iste_data 对象 info，用来存储每个 POI 的信息

                    QJsonObject json_data = json_value.toArray().at(i).toObject();//提取数组中的第 i 个元素，并将其转换为 QJsonObject。
                    info.lonlat  = json_data.value("lonlat").toString();//提取每个 POI 数据中的不同字段
                    info.phone   = json_data.value("phone").toString();
                    info.address = json_data.value("address").toString();
                    info.name   = json_data.value("name").toString();

                    iste_Data.append(info);//将提取的数据添加到容器中
                }
            }
        }
        break;
    case 2:  // 统计
        iste_Data.clear(); //清空容器
        if(json_object.contains("statistics"))
        {
            QJsonValue json_value = json_object.value("statistics");
            if(json_value.isObject())
            {
                QJsonObject json_data = json_value.toObject();
                if(json_data.contains("priorityCitys"))
                {
                    QJsonValue json_value1 = json_data.value("priorityCitys");

                    if(json_value1.isArray())
                    {
                        for (int i = 0; i < json_value1.toArray().size(); ++i) {
                            iste_data info;
                            //从每个城市数据中提取 "lonlat"（经纬度）和 "adminName"（城市名称）字段的值
                            QJsonObject json_data1 = json_value1.toArray().at(i).toObject();
                            info.lonlat  = json_data1.value("lonlat").toString();
                            info.name   = json_data1.value("adminName").toString();

                            iste_Data.append(info);
                        }

                    }
                }
            }
        }
        break;
    case 3:  // 行政区
        iste_Data.clear(); //清空容器

        if(json_object.contains("area"))
        {
            QJsonValue json_value = json_object.value("area");

            QJsonObject json_data = json_value.toObject();

            iste_data info;

            info.lonlat = json_data.value("lonlat").toString();
            info.name   = json_data.value("name").toString();

            iste_Data.append(info);
        }
        break;
    case 4:  // 建议词搜索
        qDebug()<<"resultType:"<<reson;
        break;
    case 5:  // 线路结果
        qDebug()<<"resultType:"<<reson;
        break;
    default:
        qDebug()<<"网址获取经纬度失败";
        break;
    }

    double lon = iste_Data[0].lonlat.split(",").at(0).toDouble();//经度部分
    double lat = iste_Data[0].lonlat.split(",").at(1).toDouble();//纬度
    emit lonlat(lon,lat);//使用 emit 关键字发出一个信号 lonlat，将提取到的经纬度 lon 和 lat 作为参数传递出去。
}
