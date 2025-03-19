#include "weather.h"
#include "ui_weather.h"

Weather::Weather(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Weather)
{
    ui->setupUi(this);

    ui->lineEdit_city->setPlaceholderText("填写要擦看的城市");  //设置 lineEdit_city的占位符文本，当输入框为空时，会显示 ，提示用户输入城市名
    //ui->widget_today->setVisible(false);                   // 隐藏widget_today内容
    QIcon icn_seek;
    icn_seek.addFile("./img/search.png");//创建了一个 QIcon 对象，并从路径 ./img/search.png 加载一个图标
    ui->pushButton_seek->setIcon(icn_seek);//将该图标设置为 pushButton_seek（一个按钮）的图标
    data_up_judge = 0;   //默认成功,0代表成功

    softKeyboard = new SoftKeyboard();//创建一个软键盘对象 softKeyboard
    //给lineEdit_city安装了事件过滤器,当 lineEdit_city 上发生事件（如键盘输入、鼠标点击等）时，这些事件会首先被发送到 Weather 类中的 eventFilter() 函数。
    ui->lineEdit_city->installEventFilter(this);
    weatherForecast = new WForecast(this);
    get_weather_timer = new QTimer;//创建一个 QTimer 对象 get_weather_timer，用来定时触发天气数据更新。

    get_weather();//调用 get_weather() 方法获取天气信息

    connect(get_weather_timer,SIGNAL(timeout()),this,SLOT(data_Updata()));//定时器定时触发，更新界面上的数据
    //将 lineEdit_city 的returnPressed信号（即按下回车键时）连接到槽函数，意味着当用户在文本框中输入城市名并按回车时，会触发天气数据获取。
    connect(ui->lineEdit_city,SIGNAL(returnPressed()),this,SLOT(get_weather()));
    connect(weatherForecast,&WForecast::data_lose,this,[=](bool check){//查询失败
        Q_UNUSED(check)
        data_up_judge = 1;
        //qDebug()<<"jing";
    });
}

Weather::~Weather()
{
    delete ui;
}

void Weather::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    //mySlidePage->resize(ui->widget_down->size());
    //qDebug()<<ui->widget_down->size();
}

void Weather::data_Updata()
{
    get_weather_timer->stop(); //停止定时器

    if(data_up_judge) //如果天气查询失败，直接返回
    {
        data_up_judge = 0;
        return;
    }


    // 获取星期
    QDate currentDate = QDate::currentDate();//QDate::currentDate() 获取 当前系统日期，返回一个 QDate 对象。
    int daywork = currentDate.dayOfWeek();//dayOfWeek() 获取当前日期是星期几，返回一个 int
    QString week;
    for (int i = 1; i < 8; ++i) {
        switch (daywork) { //根据数字获取当前星期对应的字符串
        case 1:
            week = "星期一";
            break;
        case 2:
            week = "星期二";
            break;
        case 3:
            week = "星期三";
            break;
        case 4:
            week = "星期四";
            break;
        case 5:
            week = "星期五";
            break;
        case 6:
            week = "星期六";
            break;
        case 7:
            week = "星期日";
            break;
        default:
            break;
        }
    }

    // 数据处理（不处理也可以）
    //ZhToPY *zhongToPY;
    QString arm[6];
    QString wind[5];
    for (int i = 0; i < 6; ++i) {
        QString chinese;
        if(i<5)
        {   //如果长度大于等于 3，意味着天气字符串可能包含 "转"（例如 "转晴"），表示天气从一种转变为另一种。
            if(weatherForecast->arm_type[i].size() >= 3){
                //使用 indexOf("转", 1) 找到 "转" 字符第一次出现的位置，+1 使得 number_arm 指向 "转" 后的第一个字符。
                int number_arm = weatherForecast->arm_type[i].indexOf("转",1) + 1;
                //使用 mid(number_arm) 方法从该位置提取字符串，即提取出 "转" 后的部分（例如，如果原始字符串是 "转晴"，则提取到 "晴"）
                chinese = weatherForecast->arm_type[i].mid(number_arm);

                //QString::fromStdString(zhongToPY->zhToPY(chinese));
                //qDebug()<<QString::fromStdString(zhongToPY->zhToPY(chinese));

            }else
            {
                chinese = weatherForecast->arm_type[i];
                        //QString::fromStdString(zhongToPY->zhToPY(chinese));
            }
        }else
            chinese = weatherForecast->arm_present;
        //qDebug()<<chinese;
        if(chinese == "晴")//根据不同天气获得不同的拼音字符串，用于后续获取对应图片
        {
            arm[i] = "qing";
        }else if(chinese == "暴雨")
        {
            arm[i] = "baoyu";
        }else if(chinese == "暴雪")
        {
            arm[i] = "baoxue";
        }else if(chinese == "暴雨")
        {
            arm[i] = "baoyu";
        }else if(chinese == "大雪")
        {
            arm[i] = "daxue";
        }else if(chinese == "大雨")
        {
            arm[i] = "dayu";
        }else if(chinese == "多云")
        {
            arm[i] = "duoyun";
        }else if(chinese == "雷阵雨")
        {
            arm[i] = "leizhenyu";
        }else if(chinese == "雾")
        {
            arm[i] = "wu";
        }else if(chinese == "小雪")
        {
            arm[i] = "xiaoxue";
        }else if(chinese == "小雨")
        {
            arm[i] = "xiaoyu";
        }else if(chinese == "阴")
        {
            arm[i] = "yin";
        }else if(chinese == "雨夹雪")
        {
            arm[i] = "yujiaxue";
        }else if(chinese == "中雪")
        {
            arm[i] = "zhongxue";
        }else if(chinese == "中雨")
        {
            arm[i] = "zhongyu";
        }else
        {
            arm[i] = "";
        }


        if(weatherForecast->wind_type[i].size() > 3){//和上面类似
            int number_arm = weatherForecast->wind_type[i].indexOf("转",1) + 1;
            wind[i] = weatherForecast->wind_type[i].mid(number_arm);
        }else
            wind[i] = weatherForecast->wind_type[i];
    }

    //qDebug()<<"arm :"<<arm[0]<<arm[1]<<arm[2]<<arm[3]<<arm[4];
    //qDebug()<<"wind:"<<wind[0]<<wind[1]<<wind[2]<<wind[3]<<wind[4];

    //  图片处理 获取对应天气的图片
    QPixmap pixm_0 = QPixmap(QString(":/img/%1.png").arg(arm[5]));//weatherForecast->arm_present
    QPixmap pixm_1 = QPixmap(QString("./img/%1.png").arg(arm[0]));//arm[0]
    QPixmap pixm_2 = QPixmap(QString("./img/%1.png").arg(arm[1]));//arm[1]
    QPixmap pixm_3 = QPixmap(QString("./img/%1.png").arg(arm[2]));//arm[2]
    QPixmap pixm_4 = QPixmap(QString("./img/%1.png").arg(arm[3]));//arm[3]
    QPixmap pixm_5 = QPixmap(QString("./img/%1.png").arg(arm[4]));//arm[4]

    QPixmap aabb = pixm_0;
    emit pixmap_data(pixm_0);
    //这行代码的含义是对 pixm_0 进行缩放处理，使其适应 ui->label_today_s_picture 的尺寸，同时保持图像的宽高比。
    pixm_0 = pixm_0.scaled(ui->label_today_s_picture->size(),Qt::KeepAspectRatio);
    pixm_1 = pixm_1.scaled(ui->label_today_s_pictures->size(),Qt::KeepAspectRatio);
    pixm_2 = pixm_2.scaled(ui->label_today_s_pictures_2->size(),Qt::KeepAspectRatio);
    pixm_3 = pixm_3.scaled(ui->label_today_s_pictures_3->size(),Qt::KeepAspectRatio);
    pixm_4 = pixm_4.scaled(ui->label_today_s_pictures_4->size(),Qt::KeepAspectRatio);
    pixm_5 = pixm_5.scaled(ui->label_today_s_pictures_5->size(),Qt::KeepAspectRatio);

    // 下面就是根据传回来的天气信息设置到页面上去显示

    // 第一页
    ui->label_city->setText(weatherForecast->city);
    ui->label_today->setText(weatherForecast->date_type[0]);
    ui->lineEdit_today_c->setText("  " + weatherForecast->temperature_type[0]);
    ui->lineEdit_today_c_realtime->setText(weatherForecast->temperature_present + "℃");
    ui->lineEdit_today_s_realtime->setText(weatherForecast->arm_present);
    ui->label_today_s_picture->setPixmap(pixm_0);
    ui->label_week->setText(week);

    ui->textEdit_today_co->clear();
    ui->textEdit_today_co->append("风      向:" + wind[0]);
    ui->textEdit_today_co->append("风      力:" + weatherForecast->wind_scale);
    ui->textEdit_today_co->append("空气指数:" + weatherForecast->AQI);
    ui->textEdit_today_co->append("湿      度:" + weatherForecast->humidity);


    // 第二页
    ui->label_today_date_4->setText(weatherForecast->date_type[3].mid(5,-1));
    ui->label_today_date_5->setText(weatherForecast->date_type[4].mid(5,-1));

    ui->label_today_c->setText(weatherForecast->temperature_type[0]);
    ui->label_today_c_2->setText(weatherForecast->temperature_type[1]);
    ui->label_today_c_3->setText(weatherForecast->temperature_type[2]);
    ui->label_today_c_4->setText(weatherForecast->temperature_type[3]);
    ui->label_today_c_5->setText(weatherForecast->temperature_type[4]);

    ui->label_wind->setText(wind[0]);
    ui->label_wind_2->setText(wind[1]);
    ui->label_wind_3->setText(wind[2]);
    ui->label_wind_4->setText(wind[3]);
    ui->label_wind_5->setText(wind[4]);

    ui->label_today_s_pictures->setPixmap(pixm_1);
    ui->label_today_s_pictures_2->setPixmap(pixm_2);
    ui->label_today_s_pictures_3->setPixmap(pixm_3);
    ui->label_today_s_pictures_4->setPixmap(pixm_4);
    ui->label_today_s_pictures_5->setPixmap(pixm_5);

}

void Weather::get_weather()
{
    QString get_city = ui->lineEdit_city->text();//这行代码从 lineEdit_city 控件（一个输入框）获取用户输入的城市名称，将其保存到 get_city 字符串变量中。
    if(!get_city.isEmpty())//如果不为空
    {
        weatherForecast->get_new_Weather(get_city);//请求这个城市的天气信息。需要延迟1s 1000 才可以获取信息
    }
    else                            //否则，请求city_1的天气信息
    {
        weatherForecast->get_Weather();
    }
    get_weather_timer->start(3600000);//启动一个1h的定时器
    ui->lineEdit_city->clear();//清空 lineEdit_city 输入框中的内容
}

//mousePressEvent 函数是一个事件处理函数，不需要显式调用。它是由 Qt 的事件系统自动触发的。
//这个函数会在 Weather 类的窗口中任何地方点击鼠标左键时触发
void Weather::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)//如果是鼠标左键点击
    {//qDebug()<<ui->stackedWidget->currentIndex()<<event->x()<<event->y();
        if(ui->stackedWidget->currentIndex()==1)//如果当前页面索引是1，就切换到0
            ui->stackedWidget->setCurrentIndex(0);
        else
            ui->stackedWidget->setCurrentIndex(1);
    }
}

bool Weather::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonRelease)//事件类型，如果是鼠标释放
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);//将事件强制转换
        if(mouseEvent->button() == Qt::LeftButton)//如果是左键
        {
            QPoint point = this->pos();//获取当前窗口的位置
            if(watched == ui->lineEdit_city)//如果当前触发的对象是lineEdit
            {
                connect(softKeyboard,&SoftKeyboard::sendInputBufferAreaText,this,[=](QString textt){
                    ui->lineEdit_city->setText(textt);
                });//当用户在 软键盘输入文字后敲下回车，这个 connect 让 lineEdit_city 更新输入框内容
                softKeyboard->showInputBufferArea("Please Input:");//调用软键盘，显示输入提示 "Please Input:"。
                softKeyboard->resize(600,320);//调整键盘大小
                softKeyboard->move(point+ui->lineEdit_city->pos());//设置键盘位置
                softKeyboard->show();//显示键盘
            }
        }
    }
    return QWidget::eventFilter(watched,event);//返回同时调用父类的事件过滤器
}

//当搜索按钮被点击时触发
void Weather::on_pushButton_seek_clicked()
{
    get_weather();
}
