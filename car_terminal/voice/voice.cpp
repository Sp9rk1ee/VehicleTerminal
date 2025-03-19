#include "voice.h"
#include "ui_voice.h"

Voice::Voice(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Voice)
{
    ui->setupUi(this);

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(onTimer1TimeOut()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(onTimer2TimeOut()));
    connect(timer3,SIGNAL(timeout()),this,SLOT(onTimer3TimeOut()));

    // 自定义的录音类
    myAudioRecorder = new AudioRecorder(this);

    // 自定义的百度识别语言类
    myAsr = new Asr(this);

    //当百度那边返回识别结果时，会触发这个槽函数，参数就是百度那边返回的识别结果
    connect(myAsr,SIGNAL(asrReadyData(QString)),this,SLOT(onAsrReadyData(QString)));
}

Voice::~Voice()
{
    delete ui;
}

// 鼠标按下，qt自动调用
void Voice::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    //这里获取了 label_2（一个标签控件）的位置和尺寸
    int label_x_min = ui->label_2->x();
    int label_x_max = ui->label_2->x() + 200;
    int label_y_min = ui->label_2->y();
    int label_y_max = ui->label_2->y() + 200;
    int mouse_x = event->x();//返回鼠标点击时的水平坐标
    int mouse_y = event->y();

    ui->label_2->setStyleSheet("image: url(:/new/prefix1/switch/start.png);");//设置样式
    //检查鼠标点击的位置是否在 label_2 标签的区域内,如果在，说明开始语音输入
    if((mouse_x <= label_x_max && mouse_x >= label_x_min) && (mouse_y <= label_y_max && mouse_y >= label_y_min))
    {
        ui->label_2->setStyleSheet("image: url(:/new/prefix1/switch/stop.png);");
//        qDebug()<<"鼠标："<<event->x()<<event->y();
//        qDebug()<<"label:"<<ui->label_2->x()<<ui->label_2->y();

        timer2->start(1500);
        ui->label->setText("正在聆听，请继续...");
    }
}

// 鼠标松开
void Voice::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    ui->label_2->setStyleSheet("image: url(:/new/prefix1/switch/start.png);");
    onTimer1TimeOut();//直接调用计时器到时会触发的函数
}

void Voice::onTimer1TimeOut()
{
    // 停止录音
    myAudioRecorder->stopRecorder();
    ui->label->setText("正在识别，请稍等...");
    timer1->stop();
    QString fileName = QCoreApplication::applicationDirPath() + "/16k.wav";//录音文件
    myAsr->getTheResult(fileName);//把这个录音结果发送给百度去获得识别结果，当有识别结果时，会发送信号asrReadyData过来，然后会触发之前绑定的槽函数
    timer3->start(30000);  // 等待识别结果
}

void Voice::onTimer2TimeOut()
{
    timer1->start(8000);//最长录音时间
    // 开始录音
    myAudioRecorder->startRecorder();
    timer2->stop();
}

void Voice::onTimer3TimeOut()
{
    ui->label->setText("请点击，开始说话...");
    timer3->stop();
}

//根据百度发回来的识别结果去执行相应的动作
void Voice::onAsrReadyData(QString str)
{
    if(str.contains("开灯"))
    {
        emit get_led(1);
    }
    else if(str.contains("关灯"))
    {
        emit get_led(0);
    }

    ui->label->setText(str);
    //调整标签的大小，使其恰好能够容纳其中的文本内容。具体来说，它会根据标签的文本内容的长度和字体大小，动态调整标签的宽度和高度。
    ui->label->adjustSize();

}
