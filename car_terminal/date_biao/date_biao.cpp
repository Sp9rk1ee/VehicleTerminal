#include "date_biao.h"

Date_biao::Date_biao(QWidget *parent)
    : QWidget(parent)
{

    //计时器的使用
    timer = startTimer(1000); // startTimer(1000) 会创建一个定时器，该定时器每 1000 毫秒触发一次 timerEvent 函数，目的是让时钟每秒更新一次。
    QTime nowtime = QTime::currentTime(); //获取当前系统时间
    h = nowtime.hour();
    m = nowtime.minute();
    s = nowtime.second();

}

Date_biao::~Date_biao()
{
}

//定时器到后会触发这个函数
void Date_biao::timerEvent(QTimerEvent *event)
{
    s++;
    if (s == 60)
       {
           s = 0;
           m++;

           if (m == 60)
           {
               m = 0;
               h++;

               if (h == 24)
               {
                   h = 0;
               }
           }
       }
}
//resize  show之类的函数会自动触发paintEvent，所以这里的paintEvent虽然没有显示调用，但实际上也被调用了
void Date_biao::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);  //必须在绘图事件中定义才会被激活，创建一个 QPainter 对象，并将当前窗口 (this，即 Date_biao 这个 QWidget) 作为绘图目标。
    painter.setRenderHint(QPainter::Antialiasing,true);  //开启抗锯齿，让绘制的线条和图形更平滑，不会出现明显的锯齿状边缘。
    QPen mypen(Qt::black,3);  //构建一只画笔mypen，颜色为黑色，线条宽度为3像素
    painter.setPen(mypen);   //告诉 painter 使用 mypen 作为当前的绘图工具，这样后续绘制的线条都会使用该画笔的颜色和宽度。
    QPoint center(this->width()/2,this->height()/2);   //计算窗口中心点的坐标，并将其存储到 center 变量中，以便后续绘图操作使用。
    painter.translate(center);//将绘图坐标系的原点 (默认在左上角) 移动到窗口中心（center）。这样后续绘制的图形就会以center为基准，而不是左上角 (0,0)。
    QPoint cen(0,0);// 定义一个原点坐标（0，0）并存储到变量cen中
    //painter.drawEllipse(cen,200,200);   //绘制时钟的外围

    //描绘大刻度上的数字
    QColor color(0,0,0);// 定义一个颜色（0，0，0）也就是黑色，并存储到变量color中
    painter.setPen(color);// 设置画笔painter的颜色为黑色
    for(int i=0;i<12;i++)
    {
        painter.rotate(30.0);//让 QPainter 旋转 30°（360° ÷ 12 = 30°），即每次循环，坐标系都会旋转 30°，这样可以绘制12个刻度。
        painter.drawLine(90,0,90,0);
        painter.drawText(-30,-92,60,50,Qt::AlignHCenter|Qt::AlignTop,QString::number(i+1));
    }

    //绘制分钟的刻度线
     for(int i=0;i<60;i++)
     {
         painter.rotate(6);// 每次旋转6°
         painter.drawLine(0,-100,0,-110); // 画一条从（0，-100）到（0，-110）的刻度线，注意向上（左）为负
     }

     //绘制小时的刻度线
    painter.setPen(Qt::blue);
    for(int i=0;i<12;i++)
    {
        painter.rotate(30);
        painter.drawLine(0,-92,0,-110);
    }

    //画圆(表盘)
    int radii_=220;
    QRectF rectangle(-radii_/2,-radii_/2,radii_,radii_); // 定义一个矩形，前两个参数是矩形左上角坐标，后两个参数是矩形长宽
    painter.drawEllipse(rectangle);//使用 painter 对象绘制一个圆形，圆形的外接矩形由前面定义的 rectangle 来确定。

    painter.end();//调用 end() 函数结束绘制操作

    QPainter painters(this);  //定义一个画家来控制秒针
    painters.setRenderHint(QPainter::Antialiasing,true);//启用抗锯齿效果，让绘制的线条更加平滑，避免锯齿状的边缘，提升绘图质量。
    mypen.setWidth(1);//设置画笔 mypen 的宽度为 1像素

    painters.setPen(mypen);//将前面定义的画笔 mypen 设置为 painters 绘图工具的画笔
    painters.translate(center);//将绘图坐标系的原点从左上角（默认）移动到窗口的前面定义的center
    painters.rotate(s*6);  //旋转绘图坐标系 s * 6 度。s 是秒数
    painters.drawLine(0,0,0,-100);  //画出秒针
    painters.end();

    QPainter painterm(this);  //定义一个画家来控制分针,创建一个 QPainter 对象 painters，并将当前窗口（this）作为绘图目标
    painterm.setRenderHint(QPainter::Antialiasing,true);//启用抗锯齿效果，让绘制的线条更加平滑，避免锯齿状的边缘，提升绘图质量。
    mypen.setWidth(4);//设置画笔 mypen 的宽度为 4 像素
    mypen.setColor(Qt::blue);//画笔颜色为蓝色
    painterm.setPen(mypen);//将前面定义的画笔 mypen 设置为 painters 绘图工具的画笔
    painterm.translate(center);//将绘图坐标系的原点从左上角（默认）移动到窗口的前面定义的center
    painterm.rotate(m*6);  //旋转绘图坐标系 m * 6 度。
    painterm.drawLine(0,0,0,-100);//画出分针
    painterm.end();

    QPainter painterh(this);  //定义一个画家来控制时针
    painterh.setRenderHint(QPainter::Antialiasing,true);
    mypen.setWidth(7);
    mypen.setColor(Qt::red);
    painterh.setPen(mypen);
    painterh.translate(center);
    painterh.rotate(h*30+m*0.5);  //时针每小时偏移30°并在原来的基础上每分钟偏移0.5°
    painterh.drawLine(0,0,0,-80);
    painterh.end();

    update();  //刷新绘图事件
}
