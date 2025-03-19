#include "widget.h"
#include "ui_widget.h"

// widget.cpp 文件主要负责管理主界面和多个功能页面的显示与切换，控制背景壁纸的设置，处理按键事件，
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this); // 它会将 Qt Designer 设计的 .ui 文件转换为 C++ 代码，并应用到当前的 QWidget（或 QMainWindow、QDialog 等）对象上。
                       // 通俗的讲它把你在 Qt Designer 里设计的界面（比如按钮、标签、输入框等）放到当前的widget（this）里。

//    ui->widget_astate->hide();
//    ui->widget_page->hide();

//    init_ = new Init_(this);
//    connect(init_,&Init_::init_accomplish,[this]{
//        init_->hide();
//        delete init_;
//        ui->widget_astate->show();
//        ui->widget_page->show();
//    });

    //  壁纸设置
    setting = new QLabel(this); // 创建一个 QLabel 对象并让setting指针指向它，并将它的父控件设置为当前窗口（this）
    setting->setPixmap(QPixmap("./bizi/1.png")); // 将一个图片设置为 QLabel 的显示内容
    setting->setScaledContents(true); //将QLabel 的显示内容设置为可以缩放。如果图片的尺寸与 QLabel 的尺寸不匹配，图片被拉伸或缩放，以适应控件的大小。
    setting->lower();//将 QLabel 控件放到当前窗口的底层。lower()方法会将控件移动到其它控件的下面，避免该控件遮挡其它控件
    setting->resize(this->size()); // 这行代码将 QLabel 的大小调整为当前窗口（this）的大小。this指的是widget

    // 页面设置  //background-color: rgb(224, 241, 214);//推荐把壁纸设置为这个颜色
    slidePage = new SlidePage(ui->widget_page);// 实例化SlidePage，传入widget_page（在widget.ui里面被定义）作为其父控件
    life = new Life(ui->widget_page,this);// 与上面同理，都是实例化
    use = new Use(ui->widget_page,this);
    tool = new Tool(ui->widget_page,this);
    //qDebug()<<ui->widget_page->size(); qDebug()<<111;
    slidePage->resize(this->width(),this->height() - this->height()*2/17 - 6); // 调整slidepage的大小
    slidePage->addPage(life); // 向slidepage添加life这个子界面，下面类似，slidePage 里 包含 3 个页面，可能可以滑动或切换来显示不同内容
    slidePage->addPage(use);
    slidePage->addPage(tool);
    ui->pushButton_life->setFixedHeight(this->height()*2/17); //pushButton_life同样在wight.ui里面定义，自己通过QTDesigner设计完后，qt自动生成的ui文件
    ui->pushButton_use->setFixedHeight(this->height()*2/17); //这三行代码都是类似的作用，设置按钮的固定高度
    ui->pushButton_tool->setFixedHeight(this->height()*2/17);

    key = new Key(this);
    connect(key,SIGNAL(main_show()),this,SLOT(exit_all()));// 为key绑定一个信号main_show()，接受信号的对象是widget，触发的槽函数是exit_all()

    //  主界面隐藏
    connect(life,SIGNAL(hide_show_life()),this,SLOT(hide_widget())); // 和上面一样，给life绑定信号和槽函数
    connect(use,SIGNAL(hide_show_use()),this,SLOT(hide_widget()));
    connect(tool,SIGNAL(hide_show_tool()),this,SLOT(hide_widget()));
    connect(tool,SIGNAL(bizi_path(QString)),this,SLOT(wallpaper_change(QString)));
    connect(tool,SIGNAL(use_name(bool)),this,SLOT(use_name(bool)));
    //  接收wifi是否可以使用
    connect(tool,&Tool::wifi_judge,[=](bool wifi_judge){ //Tool中的信号会被传递给槽函数（lamda表达式），槽函数包含life中的wifi_judge函数和use中的，
        life->wifi_judge(wifi_judge);   // 括号里的wifi_judge是信号wifi_judge传递过来的参数
        use->wifi_judge(wifi_judge);
    });
    //  由于天气功能在不同类中使用，传输信息
    connect(use,&Use::weather_show,[=]{  // 和上面类似，绑定信号和槽函数
       life->weather_diaplay(true);
    });
    //  按键颜色
    // 和上面的类似，信号携带一个参数pageIndex，该参数会传递给lamda表达式，表达式根据不同的参数做出不同的动作，主要是更改按钮的背景色
    connect(slidePage,&SlidePage::getCurrentPageIndexChanged,[=](int pageIndex){
        switch (pageIndex) {
        case 0:
            ui->pushButton_life->setStyleSheet("background-color: qconicalgradient(cx:0.5, cy:1, angle:270, stop:0.125 rgba(0, 85, 255, 255), stop:0.510526 rgba(224, 241, 214, 255), stop:0.515789 rgba(224, 241, 214, 255), stop:0.875 rgba(0, 85, 255, 255));");
            ui->pushButton_use->setStyleSheet("background-color: rgb(0, 85, 255);");
            ui->pushButton_tool->setStyleSheet("background-color: rgb(0, 85, 255);");//background-color: rgb(0, 85, 255);
            break;
        case 1:
            ui->pushButton_life->setStyleSheet("background-color: rgb(0, 85, 255);");
            ui->pushButton_use->setStyleSheet("background-color: qconicalgradient(cx:0.5, cy:1, angle:270, stop:0.125 rgba(0, 85, 255, 255), stop:0.510526 rgba(224, 241, 214, 255), stop:0.515789 rgba(224, 241, 214, 255), stop:0.875 rgba(0, 85, 255, 255));");
            ui->pushButton_tool->setStyleSheet("background-color: rgb(0, 85, 255);");
            break;
        case 2:
            ui->pushButton_life->setStyleSheet("background-color: rgb(0, 85, 255);");
            ui->pushButton_use->setStyleSheet("background-color: rgb(0, 85, 255);");
            ui->pushButton_tool->setStyleSheet("background-color: qconicalgradient(cx:0.5, cy:1, angle:270, stop:0.125 rgba(0, 85, 255, 255), stop:0.510526 rgba(224, 241, 214, 255), stop:0.515789 rgba(224, 241, 214, 255), stop:0.875 rgba(0, 85, 255, 255));");
            break;
        default:
            qDebug()<<"返回页面数亮错误，返回值："<<pageIndex;
            break;
        }
    });
}

Widget::~Widget() // 析构函数
{
    delete ui;
    delete key;
}
// 当键盘的某个按键被按下时，该槽函数会被触发
void Widget::keyPressEvent(QKeyEvent *event)
{
    key->keyPressEvent_1(event); // 调用我们自定义的Key类中的函数keyPressEvent_1
    QWidget::keyPressEvent(event);// 调用QWidget自带的ketPressEvent函数，一般不会做什么处理
}

// 当键盘某个按键被释放
void Widget::keyReleaseEvent(QKeyEvent *event)
{
    key->keyReleaseEvent_1(event); // 和上面同理
    QWidget::keyReleaseEvent(event);
}

void Widget::exit_all()
{
    ui->widget_astate->show(); //显示这个控件
    setting->show();          // 显示壁纸
    slidePage->show();      // 显示这个页面切换控件
    life->hide_all();       // 调用life的hide_all函数，会隐藏一些东西
    use->hide_all();
    tool->hide_all();
}

// 隐藏一些东西，由于或者槽函数属于Widget类，所以ui指的是Widget
void Widget::hide_widget()
{
    ui->widget_astate->hide();
    setting->hide();          //  壁纸
    slidePage->hide();
}
// 自动连接的槽函数，和clicke信号相关联，具体可以问gpt，当pushbutton_life被点击时触发，因为
// 这个槽函数的命名符合一些规则，所以自动连接了，不需要调用connect显式链接
void Widget::on_pushButton_life_clicked()
{
    slidePage->resize(this->width(),this->height() - this->height()*2/17 - 6); // 调整slidepage的大小
    //调整几个按钮的颜色
    ui->pushButton_life->setStyleSheet("background-color: qconicalgradient(cx:0.5, cy:1, angle:270, stop:0.125 rgba(0, 85, 255, 255), stop:0.510526 rgba(224, 241, 214, 255), stop:0.515789 rgba(224, 241, 214, 255), stop:0.875 rgba(0, 85, 255, 255));");
    ui->pushButton_use->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pushButton_tool->setStyleSheet("background-color: rgb(0, 85, 255);");
    slidePage->setPage(0); //设置当前页面为第0页，它会把生活页面显示到屏幕上，具体显示life里的什么东西，由life的构造函数决定，看函数里创建了什么
}

// 和上面life同理
void Widget::on_pushButton_use_clicked()
{
    ui->pushButton_life->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pushButton_use->setStyleSheet("background-color: qconicalgradient(cx:0.5, cy:1, angle:270, stop:0.125 rgba(0, 85, 255, 255), stop:0.510526 rgba(224, 241, 214, 255), stop:0.515789 rgba(224, 241, 214, 255), stop:0.875 rgba(0, 85, 255, 255));");
    ui->pushButton_tool->setStyleSheet("background-color: rgb(0, 85, 255);");
    slidePage->setPage(1);
}

// 和上面同理
void Widget::on_pushButton_tool_clicked()
{
    ui->pushButton_life->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pushButton_use->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pushButton_tool->setStyleSheet("background-color: qconicalgradient(cx:0.5, cy:1, angle:270, stop:0.125 rgba(0, 85, 255, 255), stop:0.510526 rgba(224, 241, 214, 255), stop:0.515789 rgba(224, 241, 214, 255), stop:0.875 rgba(0, 85, 255, 255));");
    slidePage->setPage(2);
}

// 切换壁纸
void Widget::wallpaper_change(QString bizi_path)
{
    qDebug()<<bizi_path;
    setting->setPixmap(QPixmap(bizi_path));
    setting->setScaledContents(true); // 这行代码设置 setting 控件的 setScaledContents 属性为 true，表示图片会被自动缩放以适应控件的大小。
}

// 显示一些东西（名字）
void Widget::use_name(bool use_name)
{
    use->useName(use_name);
    tool->useName(use_name);
}
