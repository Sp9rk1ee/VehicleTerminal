#include "asr.h"

Asr::Asr(QWidget *parent)
    : QWidget{parent}
{
    networkAccessManager = new QNetworkAccessManager(this);//创建一个 QNetworkAccessManager 实例，它用于处理所有的网络请求。

    QString fileName = QCoreApplication::applicationDirPath() + "/16k.wav";//文件路径
    file.setFileName(fileName);// file 对象的文件名为上面定义的 fileName，即指向名为 16k.wav 的音频文件

    if(file.exists())
        qDebug()<<fileName;

    //构建获取百度云语音识别服务的 token 请求的 URL。
    //token_org 是一个格式化的字符串模板，api_key 和 secret_key 是你的百度云开发者凭证。
    //使用 arg() 方法替换 token_org 中的 %1 和 %2 占位符，填充为实际的 api_key 和 secret_key。
    tokenUrl = QString(token_org).arg(api_key).arg(secret_key);

    QByteArray requestData;
    requestData.clear();
    //调用 requestNetwork() 函数来发送网络请求，获取 token。tokenUrl 是用来获取 token 的 URL，requestData 是请求的内容
    requestNetwork(tokenUrl,requestData);
}

Asr::~Asr()
{

}

// 请求网络
void Asr::requestNetwork(QString url, QByteArray requestData)
{
    // 网络请求
    QNetworkRequest networkRequest;//QNetworkRequest 是 Qt 中用于设置和发起 HTTP 请求的对象。这个对象用于存储请求的 URL、头信息、以及其他配置

    // 开发板需要加一些安全配置重可以访问https
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);//关闭服务器验证
    config.setProtocol(QSsl::TlsV1SslV3);//指定使用的 SSL/TLS 协议版本
    networkRequest.setSslConfiguration(config);//使用上面的设置

    // 以json格式返回。这一行设置了请求头，表示请求体的内容是 JSON 格式，且字符编码为 UTF-8。
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=UTF-8");

    // 设置pcm编码，采样率为16000.这里设置了请求头中的 Content-Type 为音频文件的格式。具体是 audio/pcm，并设置采样率为 16000 Hz（通常适用于语音识别）。
    networkRequest.setRawHeader("Content-Type",QString("audio/pcm;rate=16000").toLatin1());

    // 设置访问地址
    networkRequest.setUrl(url);

    //这一行通过 QNetworkAccessManager 发起一个 POST 请求。请求发送到 url，并携带 requestData 作为请求体（可能是音频数据、JSON 数据等）。
    QNetworkReply *newReply = networkAccessManager->post(networkRequest,requestData);
    //信号表示请求完成。连接到 replyFinished() 槽函数，当请求完成后执行该槽函数，处理响应结果。
    connect(newReply,SIGNAL(finished()),this,SLOT(replyFinished()));
    //信号表示有数据可以读取。连接到 readyReadData() 槽函数，用于逐步读取返回的数据。
    connect(newReply,SIGNAL(readyRead()),this,SLOT(readyReadData()));

}

//把音频文件填入到请求体中然后发送网络请求
void Asr::getTheResult(QString fileName)
{
    file.setFileName(fileName);
    if(!file.exists())
    {
        qDebug()<<"已返回，文件"<<fileName<<"不存在";
        return;
    }

    QByteArray requestData;
    file.open(QIODevice::ReadOnly);
    requestData = file.readAll();//把音频文件填入到请求体中
    file.close();
    //使用 QString::arg() 方法，将本地主机名和访问令牌（accessToken）替换到 server_api 字符串中，构造出最终的 API 请求 URL serverApiUrl
    serverApiUrl = QString(server_api).arg(QHostInfo::localHostName()).arg(accessToken);
    //发送正儿八经的语音识别网络请求
    requestNetwork(serverApiUrl,requestData);
}

// 读取数据，当请求有相应时触发
void Asr::readyReadData()
{
    QNetworkReply *reply = (QNetworkReply*)sender();//获取网络返回的响应
    QByteArray data = reply->readAll();

    if(reply->url() == QUrl(tokenUrl))//如果相应是tokenURL的响应，也就是获取token的请求的响应
    {
        qDebug()<<QString(data);
        QString key = "access_token";//定义一个 key 字符串，表示 JSON 数据中用于获取 token 的键名。

        QString trmp = getJsomValue(data,key);//调用 getJsomValue方法，从响应数据（data）中提取对应 key（即 access_token）的值，并赋值给 trmp。
        accessToken = trmp;//把获取到的token最终存储到accessToeken中

        qDebug()<<accessToken;
        qDebug()<<"获取token成功，可以调用getTheResult设置语音路径返回结果";
    }

    if(reply->url() == QUrl(serverApiUrl))//如果是请求语音识别的响应
    {
        qDebug()<<QString(data);
        QString key = "result";

        QString temp = getJsomValue(data,key);//和上面类似，获取结果

        emit asrReadyData(temp);//将获取到的识别结果通过信号发送给某个槽函数
        qDebug()<<temp;
    }
}

// 请求完成处理，释放对象
void Asr::replyFinished()
{
    QNetworkReply *reply =(QNetworkReply*)sender();
    if(reply->url() == QUrl(tokenUrl))
    {
//          QByteArray requestData;

//          file.open(QIODevice::ReadOnly);
//          requestData = file.readAll();
//          file.close();

//          serverApiUrl = QString(server_api).arg(QHostInfo::localHostName()).arg(accessToken);

//          requestNetwork(serverApiUrl,requestData);
    }

    reply->deleteLater();
    reply = nullptr;
}

// Json解释分离数据
//从一个 JSON 格式的字节数组（QByteArray）中提取指定 key 的值，并将这个值作为 QString 返回。
QString Asr::getJsomValue(QByteArray ba, QString key)
{
    QJsonParseError parseError;
    //这行代码将字节数组 ba 转换成一个 QJsonDocument 对象。
    //如果 ba 中包含的是有效的 JSON 格式数据，jsonDocument 将会被成功创建。parseError 用来记录解析过程中是否发生了错误。
    QJsonDocument jsonDocument = QJsonDocument::fromJson(ba,&parseError);

    if(parseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            // jsonDocument转化为json对象
            QJsonObject jsonObj = jsonDocument.object();

            if(jsonObj.contains(key))
            {
                QJsonValue jsonVal = jsonObj.value(key);

                if(jsonVal.isString())
                {
                    return jsonVal.toString();
                }else if(jsonVal.isArray())
                {
                    // 转换成jsonArray
                    QJsonArray arr = jsonVal.toArray();
                    // 获取第一个元素
                    QJsonValue jv = arr.at(0);
                    return jv.toString();
                }
            }
        }
    }

    return nullptr;
}
