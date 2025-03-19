#include "audiorecorder.h"

AudioRecorder::AudioRecorder(QWidget *parent)
    : QWidget{parent}
{
    // 录制音频的类
    m_audioRecorder = new QAudioRecorder(this);

    // 用于探测缓冲区的数据
    m_probe = new QAudioProbe(this);
    // 跟新录音level显示
    /*
    想象一下 QAudioProbe 就像是一个音频监视器，实时观察录音过程中的音频数据流。
    每当它捕捉到新的音频数据（也就是缓冲区数据），它就会发出一个信号（audioBufferProbed）。
    程序通过这行代码告诉它：“当你发现新的音频数据时，去调用 processBuffer 函数处理它。”    
    */
    connect(m_probe,&QAudioProbe::audioBufferProbed,this,&AudioRecorder::processBuffer);
    // 设置探测对象
    m_probe->setSource(m_audioRecorder);

    // 扫描本地声卡设备
    devicesVar.append(QVariant(QString()));//向 devicesVar 容器中添加一个空的 QVariant 对象，存储一个空字符串。
    for (auto &device: m_audioRecorder->audioInput() ) {//遍历m_audioRecorder中的所有可用的音频输入设备。audioInput()返回一个包含音频输入设备名称的列表。
        devicesVar.append(QVariant(device));//把可用的音频输入设备添加到devicesVar中
        qDebug()<<"本地声卡设备："<<device;
    }

    // 音频编码
    codecsVar.append(QVariant(QString()));//在 codecsVar 容器中添加一个初始的空值
    for (auto &codecName: m_audioRecorder->supportedAudioCodecs() ) {//遍历 QAudioRecorder 支持的所有音频编码格式。
        codecsVar.append(QVariant(codecName));
        qDebug()<<"音频编码:"<<codecName;
    }

    // 容器支持的格式
    containersVar.append(QVariant(QString()));
    for (auto &containerName: m_audioRecorder->supportedContainers()) {//遍历 QAudioRecorder 支持的所有音频容器格式
        containersVar.append(QVariant(containerName));
        qDebug()<<"支持的格式:"<<containerName;
    }

    // 采样率
    sampleRateVar.append(QVariant(0));
    // 百度语音识别只支持8000、16000采样率
    sampleRateVar.append(QVariant(8000));
    sampleRateVar.append(QVariant(16000));
    for (int sampleRate: m_audioRecorder->supportedFrameRates()) {//所有支持的音频采样率（帧率）的列表。
        sampleRateVar.append(QVariant(sampleRate));
        qDebug()<<"采样率:"<<sampleRate;
    }


    // 通道.声道数量，一声道二声道这样
    channelsVar.append(QVariant(-1));
    channelsVar.append(QVariant(1));
    channelsVar.append(QVariant(2));
    channelsVar.append(QVariant(4));

    // 质量
    qualityVar.append(QVariant(int(QMultimedia::LowQuality)));
    qualityVar.append(QVariant(int(QMultimedia::NormalQuality)));
    qualityVar.append(QVariant(int(QMultimedia::HighQuality)));

    // 比特率
    bitratesVar.append(QVariant(0));
    bitratesVar.append(QVariant(32000));
    bitratesVar.append(QVariant(64000));
    bitratesVar.append(QVariant(96000));
    bitratesVar.append(QVariant(128000));

    // 录音类信号槽连接
    //每当录音时长更新时，durationChanged 信号就会被触发，并且会调用 updateProgress 函数来处理这一变化。
    connect(m_audioRecorder,&QAudioRecorder::durationChanged,this,&AudioRecorder::updateProgress);
}

AudioRecorder::~AudioRecorder()
{

}

//开始录音
void AudioRecorder::startRecorder()
{
    /*备注：录音需要设置为16000采样率和通道为1,
     * 保存wav文件需要设置成audio/x-wav（container文件格式）
     */

    // 如果录音已停止，则开始录音
    if(m_audioRecorder->state() == QMediaRecorder::StoppedState)
    {
        // 设置默认的录音设备
        m_audioRecorder->setAudioInput(devicesVar.at(0).toString());

        // 录音设置
        QAudioEncoderSettings settings;
        settings.setCodec(codecsVar.at(0).toString());//音频编码格式
        settings.setSampleRate(sampleRateVar[2].toInt());//采样率
        settings.setBitRate(bitratesVar[0].toInt());//比特率
        settings.setChannelCount(channelsVar[1].toInt());//通道数
        settings.setQuality(QMultimedia::EncodingQuality(qualityVar[0].toInt(0)));//质量

        // 以恒定的质量录制，可选恒定的波特率
        settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);// 恒定质量编码

        // IMX6U第20个支持的格式为audio/x_wav
        QString container = containersVar.at(20).toString();

        // 使用配置
        m_audioRecorder->setEncodingSettings(settings,QVideoEncoderSettings(),container);//第二个参数是视频录制的，这里无用

        // 录音保存为16k.wav文件
        m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(tr("./16k.wav")));

        // 开始录音
        m_audioRecorder->record();
    }
}

void AudioRecorder::stopRecorder()
{
    // 停止录音
    m_audioRecorder->stop();
}

//每当录音进行时，录制时长发生变化时，updateProgress 就会被调用。实时打印录制时长
void AudioRecorder::updateProgress(qint64 durtion)
{
    Q_UNUSED(durtion);//关闭提示

    if(m_audioRecorder->error() != QMediaRecorder::NoError)
    {
        return;
    }

    // 打印录制时长
    qDebug()<<"录制时长:"<<durtion/1000;
}

void AudioRecorder::processBuffer(const QAudioBuffer &buffer)
{
    // 根据通道数目需要显示count个level
    int count = buffer.format().channelCount();
    // 打印通道数
    qDebug()<<"通道数:"<<count;

    // 设置level的值
    //调用 getBufferLevels() 函数，从音频缓冲区 buffer 中提取每个通道的音量等级。levels 是一个 QVector<qreal> 类型的数组，包含每个通道的音量等级。
    QVector<qreal>levels = getBufferLevels(buffer);
    for (int i=0;i<levels.count();++i)
    {
        //打印音量等级
        qDebug()<<"音量等级"<<levels.at(i);
    }
}

void AudioRecorder::clearAudioLevels()
{
    //...
}

//这个函数返回给定音频格式的最大可能采样值
qreal AudioRecorder::getPeakValue(const QAudioFormat &format)
{
    // 只支持最常见的音频格式
    if(!format.isValid())//判断格式是否有效
    {
        return qreal(0);
    }

    if(format.codec() != "audio/pcm")//如果音频编码格式不是 audio/pcm（也就是未压缩的音频格式），则返回 0，因为该函数只支持 PCM 格式
    {
        return qreal(0);
    }

    switch(format.sampleType())//音频样本类型
    {
    case QAudioFormat::Unknown:
        break;
    case QAudioFormat::Float:
        if(format.sampleSize() != 32)  // 不支持其他事例格式
        {
            return qreal(0);
        }
        return qreal(1.00003);
    case QAudioFormat::SignedInt:
        if(format.sampleSize() == 32)
            return qreal(INT_MAX);
        if(format.sampleSize() == 16)
            return qreal(SHRT_MAX);
        if(format.sampleSize() == 8)
            return qreal(CHAR_MAX);
        break;
     case QAudioFormat::UnSignedInt:
        if(format.sampleSize() == 32)
            return qreal(UINT_MAX);
        if(format.sampleSize() == 16)
            return qreal(USHRT_MAX);
        if(format.sampleSize() == 8)
            return qreal(UCHAR_MAX);
        break;
    }
    return qreal(0);
}

QVector<qreal> AudioRecorder::getBufferLevels(const QAudioBuffer &buffer)
{
    QVector<qreal> values;
    //这段代码检查音频缓冲区的格式是否有效，并且是否使用小端字节顺序
    if(!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
        return values;

    if(buffer.format().codec() != "audio/pcm")//检查音频编码格式
        return values;

    int channelCount = buffer.format().channelCount();//获取通道数量
    values.fill(0,channelCount);//用 0 填充 values 向量以初始化每个通道的音量等级。
    qreal peak_value = getPeakValue(buffer.format());//调用 getPeakValue 函数来获取音频格式的最大采样值。
    if(qFuzzyCompare(peak_value,qreal(0)))//若峰值为 0，则返回空的 values 向量，表明未能获取有效的峰值。
        return values;
    //根据不同的音频样本类型（QAudioFormat::sampleType）和样本大小（sampleSize），计算音频缓冲区中的每个通道的音量级别，并对其进行归一化处理
    switch (buffer.format().sampleType()){
    case QAudioFormat::Unknown:
    case QAudioFormat::UnSignedInt:
        if(buffer.format().sampleSize() == 32)
        {
            values = getBufferLevels(buffer.constData<quint32>(),buffer.frameCount(),channelCount);
        }
        if(buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<quint16>(),buffer.frameCount(),channelCount);
        if(buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<quint8>(),buffer.frameCount(),channelCount);
        for (int i = 0; i < values.size(); ++i) {
            values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
        }
        break;
    case QAudioFormat::Float:
        if(buffer.format().sampleSize() == 32){
            values = getBufferLevels(buffer.constData<float>(),buffer.frameCount(),channelCount);
            for (int i = 0; i < values.size(); ++i) {
                values[i] /= peak_value;
            }
        }
        break;
    case QAudioFormat::SignedInt:
        if(buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<quint32>(),buffer.frameCount(),channelCount);
        if(buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<quint16>(),buffer.frameCount(),channelCount);
        if(buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<quint8>(),buffer.frameCount(),channelCount);
        for (int i = 0; i < values.size(); ++i) {
            values[i] /= peak_value;
        }
        break;
    }

    return values;
}

//计算音频缓冲区（buffer）中每个通道的最大音量级别，并返回这些最大值。具体来说，这段代码的目的是遍历音频缓冲区的每一帧数据，计算每个通道的最大音量值
template<class T>
QVector<qreal> AudioRecorder::getBufferLevels(const T *buffer, int frames, int channels)
{
    QVector<qreal> max_values;
    max_values.fill(0,channels);

    for (int i = 0; i < frames; ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(qreal(buffer[i*channels +j]));
            if(value > max_values.at(j))
                max_values.replace(j,value);
        }

    }

    return max_values;
}
