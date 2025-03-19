#include "wforecast.h"

WForecast::WForecast(QWidget *parent,QString city)
    : QWidget{parent}
{
    city_1 = city;//city_1 是 WForecast 类的成员变量，用于存储 当前查询的城市名称

    request_weather = new QNetworkAccessManager;//QNetworkAccessManager 用于发送网络请求，request_weather 是指向该对象的指针

    //get_Weather();

    //当 request_weather发出的请求完成后，finished(QNetworkReply*) 信号会被触发
    // QNetworkReply 包含了网络请求的响应数据，使用它可以获取服务器返回的内容
    connect(request_weather,SIGNAL(finished(QNetworkReply*)),this,SLOT(json_weather(QNetworkReply*)));
}

WForecast::~WForecast()
{
    delete request_weather;
}

//应该是获取city_1这个城市的天气
void WForecast::get_Weather()
{
    get_new_Weather(city_1);
}

//解析请求回来的天气数据并填充到类成员变量里
void WForecast::json_weather(QNetworkReply *reply)
{
    QString all = reply->readAll();//从 QNetworkReply对象中读取所有响应数据，并将其存储到all字符串中。这个数据是从网络请求返回的原始JSON格式的字符串。
    //qDebug()<<all;
    QJsonParseError json_error;//创建一个 QJsonParseError 对象，用于捕捉 JSON 解析错误
    //这行代码的作用是将一个字符串（all）转换成一个QJsonDocument对象。具体来说，它将包含JSON格式数据的字符串解析成Qt可以操作的JSON数据结构。
    QJsonDocument json_recv = QJsonDocument::fromJson(all.toUtf8(),&json_error); // 解析json对象
    //这行代码的作用是从QJsonDocument中提取出一个QJsonObject，这个QJsonObject表示了JSON字符串中的对象部分。你可以用它来访问JSON对象中的各个键值对。
    QJsonObject object = json_recv.object();
    reson = object.value("reason").toString();// 获取 object 中键为 "reason" 的值,reason一般用于描述查询是否成功
    if(reson != "查询成功!")
    {
        qDebug()<<"网址获取天气失败";
        emit data_lose(1);//发送信号，表示查询失败
        return;
    }

    if(object.contains("result"))
    {
        QJsonValue value = object.value("result");//获取result的键值，一般存储了查询结果

        if(value.isObject())//检查value是不是一个json对象
        {
            QJsonObject object_1 = value.toObject();//将 QJsonValue 类型的 value 转换成 QJsonObject 类型，并赋值给 object_1。
            city = object_1.value("city").toString();//从object_1 中获取键 "city" 对应的值，并将该值转换为 QString 类型，然后赋值给变量 city
            if(object_1.contains("realtime"))//检查 JSON 对象中是否包含 "realtime" 这个键。
            {
                QJsonValue value_1 = object_1.value("realtime");//获取 JSON 对象中 "realtime" 键对应的值
                //qDebug()<<"value_1 realtime";
                QJsonObject wather = value_1.toObject();//将 QJsonValue 转换为 QJsonObject，以便可以进一步提取其中的键值对。
                humidity = wather.value("humidity").toString();// 获取 wather 对象中的 "humidity" 键对应的值，这里是湿度信息。
                AQI  = wather.value("aqi").toString();//空气质量指数值
                wind_scale = wather.value("power").toString();//风力等级
                temperature_present = wather.value("temperature").toString();//温度
                arm_present = wather.value("info").toString();//天气状况
            }

            if(object_1.contains("future"))//未来
            {
                QJsonValue value_1 = object_1.value("future");
                if(value_1.isArray())//判断 value_1 是否是一个 JSON 数组。
                {
                    for (int i = 0; i < 5; ++i) {//未来五天天气
                        QJsonObject wather = value_1.toArray().at(i).toObject();//获取第i个json对象
                        wind_type[i] = wather.value("direct").toString();//风向
                        arm_type[i]  = wather.value("weather").toString();//天气状况
                        date_type[i] = wather.value("date").toString();//日期
                        temperature_type[i] = wather.value("temperature").toString();//温度
                    }
                }
            }
        }
    }
    emit data_updating();  //暂时没用到
//    qDebug()<<"city               "<<city;
//    qDebug()<<"wind_type[5]       "<<wind_type[0]<<wind_type[1]<<wind_type[2]<<wind_type[3]<<wind_type[4];
//    qDebug()<<"arm_type[5]        "<<arm_type[0]<<arm_type[1]<<arm_type[2]<<arm_type[3]<<arm_type[4];
//    qDebug()<<"date_type[5]       "<<date_type[0]<<date_type[1]<<date_type[2]<<date_type[3]<<date_type[4];
//    qDebug()<<"temperature_type[5]"<<temperature_type[0]<<temperature_type[1]<<temperature_type[2]<<temperature_type[3]<<temperature_type[4];
//    qDebug()<<"humidity           "<<humidity;
//    qDebug()<<"AQI                "<<AQI;
//    qDebug()<<"wind_scale         "<<wind_scale;
//    qDebug()<<"temperature_present"<<temperature_present;
//    qDebug()<<"arm_present        "<<arm_present;

}

void WForecast::get_new_Weather(QString city)
{
    city_1 = city;
    //qDebug()<<"city:"<<city;
    QNetworkRequest request;//创建一个 QNetworkRequest 对象 request。QNetworkRequest 用于表示一个 HTTP 请求，后续将为其设置 URL 和其他相关参数。
    //arg(city) 将 weather_api 字符串中的占位符 %1 替换为传入的 city 名称，生成请求的完整 URL（即请求某个城市的天气数据）。
    //然后，通过 setUrl 方法将这个完整的 URL 设置为 request 对象的 URL。
    request.setUrl(QUrl(weather_api.arg(city)));
    //qDebug()<<"网站："<<QString("http://apis.juhe.cn/simpleWeather/query?city=%1&key=251518e073ef6c3c9504dd286c3f6a86").arg(city);
    //调用 request_weather（QNetworkAccessManager 对象）的 get() 方法，发送一个 GET 请求到 request 中设置的 URL，开始请求天气数据。
    request_weather->get(request);
}
