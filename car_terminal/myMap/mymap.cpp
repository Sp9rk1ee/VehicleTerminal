#include "mymap.h"
#include "ui_mymap.h"

MyMap::MyMap(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyMap)
{
    ui->setupUi(this);

    longitudeLatitude = new LongitudeLatitude(this);
    longitudeLatitude->get_LongitudeLatitude("内蒙古大学");//请求内蒙古大学的经纬度

    softKeyboard = new SoftKeyboard();
    ui->lineEdit_seek->installEventFilter(this);//安装一个事件过滤器，将事件传递给 MyMap 类来进行处理。

    map = new Map(this);

    map_show = new QLabel(this);//创建一个新的 QLabel（map_show），用于显示地图
    map_show->lower();
    map_show->resize(this->size());

    m_zoom = 14;
    mouse_number = 0;

    connect(longitudeLatitude,SIGNAL(lonlat(double,double)),this,SLOT(get_map(double,double)));
    connect(map,&Map::map_image,this,&MyMap::map_image_show);
    connect(ui->lineEdit_seek,&QLineEdit::returnPressed,this,&MyMap::on_pushButton_seek_clicked);
}

MyMap::~MyMap()
{
    delete ui;
    delete softKeyboard;
}

//通过经纬度来获取对应位置的地图图像
void MyMap::get_map(double longitude, double latitude)
{
    //qDebug()<<qSetRealNumberPrecision(10)<<"longitude:"<<longitude<<"latitude:"<<latitude;
    m_longitude = longitude;
    m_latitude = latitude;
    map->get_map(longitude,latitude,m_zoom);

}

//把获取到的地图显示出来
void MyMap::map_image_show(QImage *map_image)
{
    ui->label_area_name->setText(longitudeLatitude->iste_Data[0].name);

    map_show->setPixmap(QPixmap::fromImage(*map_image));

//    QPalette palettee = this->palette();
//    palettee.setBrush(QPalette::Background,QPixmap::fromImage(*map_image));
//    this->setPalette(palettee);
}

//当搜索按钮被点击时触发
void MyMap::on_pushButton_seek_clicked()
{
    if(ui->lineEdit_seek->text().isEmpty())
    {
        qDebug()<<"查询列表为空";
        return;
    }
    longitudeLatitude->get_LongitudeLatitude(ui->lineEdit_seek->text());
}

void MyMap::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<"鼠标按下";
    if(event->button() == Qt::LeftButton)  // 鼠标左键按下
    {
        isMousePressed = true;
        mouse_number = 0;
        lastMousePos = event->globalPos();//获取当前鼠标的位置，并将其存储在 lastMousePos 中。
    }
    QWidget::mousePressEvent(event);
}

void MyMap::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug()<<"鼠标松开";
    if (event->button() == Qt::LeftButton) {
            isMousePressed = false;

            if(!ui->widget_on->isVisible()  && mouse_number < 1)  // 获取搜索栏是否显示状态
            {
                ui->widget_on->show();//如果没显示，则显示
            }else
            {
                int mouse_y = this->mapFromGlobal(QCursor().pos()).y();//获取鼠标释放时的 Y 坐标。mapFromGlobal 将全局坐标转换为相对于当前窗口的坐标。
                int widget_y = ui->widget_down->y();//获取 widget_down 小部件的 Y 坐标（相对于当前窗口的坐标）
                if(mouse_y <= widget_y)//如果鼠标松开时的 Y 坐标小于或等于 widget_down 的 Y 坐标，则不进行任何操作，直接返回。
                    return;

                ui->widget_on->hide();//否则隐藏
            }
        }
        QWidget::mouseReleaseEvent(event);
}

void MyMap::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)  //鼠标左键按下移动
    {
        if (isMousePressed && mouse_number < 1) {
            // 计算鼠标移动的距离
            QPoint delta = event->globalPos() - lastMousePos;
            //qDebug()<<delta.x()<<delta.y();
            int ratio = m_zoom * 20;
            if (delta.x() > 0) {
                m_longitude = m_longitude - (double)delta.x() / ratio;
                //qDebug()<<"鼠标向右移动";
            } else if (delta.x() < 0) {
                m_longitude = m_longitude - (double)delta.x() / ratio;
                //qDebug()<<"鼠标向左移动";
            }

            if (delta.y() > 0) {
                m_latitude = m_latitude + (double)delta.y() / ratio;
                //qDebug()<<"鼠标向下移动";
            } else if (delta.y() < 0) {
                m_latitude = m_latitude + (double)delta.y() / ratio;
                //qDebug()<<"鼠标向上移动";
            }
            //qDebug()<<(double)delta.x()/ratio<<(double)delta.y()/ratio<<m_longitude<<m_latitude;
            // 更新控件的位置
            move(pos() + delta);
            // 更新上次鼠标的位置
            lastMousePos = event->globalPos();
            map->get_map(m_longitude,m_latitude,m_zoom);//根据移动后的经纬度获取新的经纬度地图图像
            mouse_number++;
            //move(pos() + delta);和map->get_map共同合作实现了按住拖动地图的效果
            }
    }
    QWidget::mouseMoveEvent(event);
}

void MyMap::on_pushButton_magnify_clicked()  // 放大
{
    m_zoom++;
    if(m_zoom >= 18)
    {
        m_zoom = 18;
        return;
    }
    map->get_map(m_longitude,m_latitude,m_zoom);
}

void MyMap::on_pushButton_reduce_clicked()  // 缩小
{
    m_zoom--;
    if(m_zoom <= 1)
    {
        m_zoom = 1;
        return;
    }
    map->get_map(m_longitude,m_latitude,m_zoom);
}

bool MyMap::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonRelease)//事件类型
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);//将事件强制转换
        if(mouseEvent->button() == Qt::LeftButton)
        {
            QPoint point = this->pos();
            if(watched == ui->lineEdit_seek)
            {
                connect(softKeyboard,&SoftKeyboard::sendInputBufferAreaText,this,[=](QString textt){
                    ui->lineEdit_seek->setText(textt);
                });
                softKeyboard->showInputBufferArea("Please Input:");
                softKeyboard->resize(600,320);
                softKeyboard->move(point+ui->lineEdit_seek->pos());
                softKeyboard->show();
            }
        }
    }
    return QWidget::eventFilter(watched,event);//返回父类的事件过滤器
}
