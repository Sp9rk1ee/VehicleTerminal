#ifndef ASR_H
#define ASR_H

#include <QWidget>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QHostInfo>

#include <QCoreApplication>

#include <QFile>

/*语音识别应用程序
 * 主要用来与将录制的音频发送到百度云语音识别服务器上，然后进行结果返回
 */
class Asr : public QWidget
{
    Q_OBJECT
public:
    Asr(QWidget *parent = nullptr);
    ~Asr();

    // 请求网络
    void requestNetwork(QString ,QByteArray);

    // 获取识别结果
    void getTheResult(QString fileName);

private slots:
    void readyReadData();  // 准备读取相应返回来的数据
    void replyFinished();  // 相应完成处理

private:
    QString tokenUrl;      // 存储获取tokenUrl地址
    QString serverApiUrl;  // 存储serverapi地址
    QString accessToken;   // 最终需要访问的token的地址

    /* 获取 token 的接口*/
    const QString token_org = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";

    /* 填写网页上申请的 appkey 如
     * g_api_key="g8eBUMSokVB1BHGmgxxxxxx" */
    const QString api_key = "miL7uNiPkhslIXIpsIl5mLi1";

    /* 填写网页上申请的 APP SECRET 如
    $secretKey="94dc99566550d87f8fa8ece112xxxxx" */
    const QString secret_key = "zobsUv31A13f91URxB6tTQ9ejSArgqpy";

    /* 百度服务器 API 接口，发送语音可返回识别结果 */
    const QString server_api = "http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";

    // 网络管理
    QNetworkAccessManager *networkAccessManager;
    QFile file;
    QString getJsomValue(QByteArray ba,QString key);

signals:
    void asrReadyData(QString);

};

#endif // ASR_H
