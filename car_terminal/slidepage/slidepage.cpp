/******************************************************************
Copyright © Deng Zhimao Co., Ltd. 1990-2021. All rights reserved.
* @projectName   slidepage
* @brief         slidepage.cpp
* @author        Deng Zhimao
* @email         1252699831@qq.com
* @net           www.openedv.com
* @date          2021-06-09
*******************************************************************/
#include "slidepage.h"
#include <QDebug>
#include <QPropertyAnimation>

// slidepage主要处理页面相关的，比如页面滑动，更换页面显示这种

SlidePage::SlidePage(QWidget *parent):
    QWidget(parent), //调用QWidget的构造函数
    pageIndex(0), // 这里这种写法代表初始化，有点类似于在构造函数体里{int a =1}这样，只不过在成员列表中这种写法更高效，这里代表把pageIndex初始化为0
    pageCount(0), // pageCount初始化为0
    draggingFlag(false) // draggingFlag初始化为False 
{
    pageIndicator.clear();  // 清空vector容器
    this->setMinimumSize(400, 300); // 设置slidepage这个窗口的最小尺寸为（400，300）
    this->setAttribute(Qt::WA_TranslucentBackground, true); // 让窗口背景透明

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignCenter); // 设置滚动内容的对齐方式为居中，注意不是滚动条，是滚动的内容

    mainWidget = new QWidget();
    mainWidget->setStyleSheet("background: transparent"); // 设置背景为透明

    scrollArea->setWidget(mainWidget); // 把mainWidget设置为scrollArea的内容区域，它会显示在scrollArea内部
    scrollArea->setStyleSheet("background: transparent");

    bottomWidget = new QWidget(this);  // 创建一个新的 QWidget 对象，作为底部的容器。
    bottomWidget->setStyleSheet("background: transparent"); // 设置背景为透明

    bottomHBoxLayout = new QHBoxLayout(); // 创建一个水平布局管理器
    // 将 bottomHBoxLayout设置为 bottomWidget的布局管理器。这意味着bottomWidget会按照 bottomHBoxLayout 所设定的方式排列其子控件。
    bottomWidget->setLayout(bottomHBoxLayout); 
    bottomHBoxLayout->setContentsMargins(0, 0, 0, 0); // 控制子控件(mainWidget中的控件)与父控件（mainWidget）四个边缘之间的距离
    bottomHBoxLayout->setAlignment(Qt::AlignCenter); // 设置布局中控件的对齐方式为居中。这意味着添加到 bottomHBoxLayout 中的控件会被居中显示。

    /* 关闭滚动条显示 */
    scrollArea->setVerticalScrollBarPolicy(  //禁用垂直滚动条，不会显示了，也不能通过滚动条来滚动，但仍然可以上下滚动
                Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy( // 禁用水平滚动条
                Qt::ScrollBarAlwaysOff);

    /* 滚屏对象 */ // 总的来说，下面三行目的是使 scrollArea 支持 
                  //  QScroller 对象管理滚动行为，用户可以在滚动区域内按住左键(触摸也被视为鼠标左键)并拖动来查看内容，而无需显示滚动条。
    scroller = QScroller::scroller(scrollArea); // 创建了一个 QScroller 对象，并将其绑定到 scrollArea 上。这样滚动区域就支持手势滚动（滑屏）
    QScroller::ScrollerGestureType gesture = QScroller::LeftMouseButtonGesture; // 定义一个手势类型， 表示使用鼠标左键进行的拖动操作作为滚动手势
    scroller->grabGesture(scrollArea, gesture); // 将手势和滚动区域绑定，通过这行代码，scrollArea 被配置为 响应鼠标左键拖动手势

    /* 获取属性 */
    // 通过 scroller->scrollerProperties()，你可以获得当前 QScroller 对象的滚动属性设置，以便后续修改。
    // 例如，可以设置滚动速度、滚动时长等。如果你想调整 QScroller 的滚动行为（例如让它滚得更快、滑动的时间更短等），
    // 你可以修改 QScrollerProperties 中的属性，并重新设置给 QScroller。
    QScrollerProperties properties = scroller->scrollerProperties();

    /* 设置滑动的时间，值越大，时间越短 */
    properties.setScrollMetric(QScrollerProperties::SnapTime, 0.5);

    /* 设置滑动速度 */
    properties.setScrollMetric(QScrollerProperties::MinimumVelocity, 1);
    scroller->setScrollerProperties(properties); // 将修改过的滚动属性重新赋值回scroller

    /* 布局 */
    hBoxLayout = new QHBoxLayout();

    hBoxLayout->setContentsMargins(0, 0, 0, 0);
    hBoxLayout->setSpacing(0); // 设置布局中控件间的距离

    mainWidget->setLayout(hBoxLayout);

    /* 定时器，用于判断用户是否是拖动屏幕，区分滑动，超过300ms表示拖动 */
    timer = new QTimer(this);

    connect(scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(hScrollBarValueChanged(int)));
    connect(scroller, SIGNAL(stateChanged(QScroller::State)), this, SLOT(onStateChanged(QScroller::State)));
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTimeOut()));
    connect(this, SIGNAL(getCurrentPageIndexChanged(int)), this, SLOT(onCurrentPageIndexChanged(int)));
}

SlidePage::~SlidePage()
{
}

void SlidePage::addPage(QWidget *w)
{
    /* 布局里添加页面 */
    hBoxLayout->addWidget(w);  //把添加进来的页面（比如life）添加到hBoxLayout布局里面，
                               // 传进来的w（比如说是life），已经在它自己的类里面定义了大小，hboxlayout就会根据传进来的w调整自己的大小
    /* 页数加一 */
    pageCount++;
    QLabel *label = new QLabel(); // 底部的label，注意不是应用生活那些，是他上方的那三个点

    label->setPixmap(QPixmap(":/icons/indicator1.png")); // 把图片应用到label里面

    pageIndicator.append(label); // 把label添加到pageindicator这个vector容器里，注意label是指针，也就是说以后可以直接通过这个容器访问到指向label的指针，
                                // 就可以直接通过操作这个容器里的指针修改label的样子

    bottomHBoxLayout->addWidget(label); // 把label添加到底部布局里
        //bottom和hlay同属一个父控件，上面hlay已经确定了自己的大小，那么bottom就自动根据父控件剩余空间调整自己的位置和大小
        // 所以虽然父控件没有给他们显示设置大小和位置，但其实它们已经根据传进来的和剩余空间自己分配好了
}

// 在 Qt 里，当 QWidget 的大小发生变化时，Qt 会自动触发 resizeEvent()，不需要手动调用。
// 例如：
// 窗口初始化 时，SlidePage 被创建并设置大小，Qt 会触发 resizeEvent()。
// 用户拖动窗口 改变 SlidePage 的大小时，Qt 也会触发 resizeEvent()。
// 代码里调用 resize() 或 setGeometry() 也会触发 resizeEvent()。
void SlidePage::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event) //该宏用于避免编译器警告：event 变量未被使用。
    scrollArea->resize(this->size());
    /* mainWidget需要比scrollArea小 */
    mainWidget->resize(this->width() * pageCount, this->height() - 4);  // 注意mainwidget（即显示的内容）是要乘以slidepage的页数的
    if (pageCount == 0)
        qDebug()<<"当前页面总数为0，请使用addPage()方法添加页面再使用！";
    else
        onCurrentPageIndexChanged(0); // 根据访问的页把下面那个点点变亮
    bottomWidget->setGeometry(0, this->height() - 20, this->width(), 20);
}

// 当滚动条滚动时触发的槽函数，用于判断是否翻页
void SlidePage::hScrollBarValueChanged(int)
{
    /* 滑动时判断当前页的下标 */
    /*
    pageIndex * this->width() 是当前页的起始位置。
    this->width() * 0.5 是当前页的中间点。
    如果滚动条位置 value 进入到当前页的后半部分，那么 pageIndex + 1，表示翻到下一页。
    否则，保持 pageIndex 不变。
    */
    pageIndex= scrollArea->horizontalScrollBar()->value() / this->width();
    pageIndex = scrollArea->horizontalScrollBar()->value()
            >= (pageIndex * this->width() + this->width() * 0.5) ? pageIndex + 1 : pageIndex;

}

/*
这个函数是 QScroller 的状态变化槽函数，用于处理滑动（滚动）事件，比如 按下、拖动、松开 时的行为。自动触发的
主要功能是 根据手势滑动来翻页，并且当手指/鼠标松开后，通过 动画平滑滚动 到目标页面。
*/
void SlidePage::onStateChanged(QScroller::State state)
{
    static int pressedValue = 0;  // 记录按下时的坐标
    static int releasedValue = 0; // 记录松开时的坐标
    static int currentPageIndex = 0; // 记录当前页面索引

    /* 如果页面数为0，返回，不做任何操作 */
    if (pageCount == 0)
        return;

    /* 松开 */
    if (state == QScroller::Inactive) {
        /* 停止定时器，防止检测到界面是缓慢拖动状态 */
        timer->stop();
        /* 记录松开时的坐标 */
        releasedValue = QCursor::pos().x();

        if(!inportFlag)  
        {
            draggingFlag = true;
        }else if(pressedValue == releasedValue)
            return;
        else
            inportFlag = true;

        /* 判断按下与松开的距离，首先先判断是不是拖动状态，如果是拖动状态，pageIndex不会变化 */
        if (!draggingFlag) { // 判断是不是属于拖动状态
            if (pressedValue - releasedValue > 20 && currentPageIndex == pageIndex)
            {
                    pageIndex++;
            }
            else
                pageIndex--;
        }

        /* 页面下标判断 */
        if (pageIndex == -1)
            pageIndex = 0;

        if (pageIndex >= pageCount)
            pageIndex = pageCount - 1;

        /* 动画 */
        // 创建一个 QPropertyAnimation 对象，目标是 scrollArea 的 水平滚动条
        // "value" 表示滚动条的 当前值，即滚动条的当前位置。通过改变这个值，滚动条的位置会发生变化。
        // 这部分也负责显示页面的切换，因为对于scrollArea而言，滚动条的变化会自动影响显示内容的变化，不需要我们去手动切换显示内容
        QPropertyAnimation *animation = new QPropertyAnimation(scrollArea->horizontalScrollBar(), "value");
        animation->setDuration(200);//设置动画的持续时间为 200毫秒，表示从开始到结束，滚动条的位置将平滑地变化，持续 200 毫秒
        animation->setStartValue(scrollArea->horizontalScrollBar()->value());//设置动画的 起始值为当前滚动条的位置 
        animation->setEasingCurve(QEasingCurve::OutCurve);// OutCurve 表示动画开始时较快，结束时逐渐减缓，这样会给人一种平滑、自然的滚动效果
        animation->setEndValue(pageIndex * this->width());//设置动画的结束值,这样计算得出的是 滚动条应该滚动到的位置，也就是目标页面的位置。
        animation->start();// 开始执行动画

        if (currentPageIndex != pageIndex) { // 如果当前页面变了
            /* 发送当前页面的位置信号 */
            emit getCurrentPageIndexChanged(pageIndex);
        }

        /* 重新赋值*/
        pressedValue = 0;
        releasedValue = 0;
        draggingFlag = false;
    }

    /* 按下 */
    if (state == QScroller::Pressed) {
        pressedValue = QCursor::pos().x();
        currentPageIndex = scrollArea->horizontalScrollBar()->value() / this->width();
        /* 按下如果超过300ms，表示用户在拖动 */
        timer->start(300); // 设置一个定时器，定时时间为300ms
    }
}

// 定时器超时时触发
void SlidePage::onTimerTimeOut()
{
    /* 拖动标志位 */
    draggingFlag = true;
    timer->stop();
}

int SlidePage::getPageCount()
{
    return pageCount;
}

int SlidePage::getCurrentPageIndex()
{
    return pageIndex;
}

//设置当前为第几页
void SlidePage::setPage(int page)
{
    int dangqian_page =  getCurrentPageIndex(); // 获得当前为第几页
    if(page - dangqian_page == 0)
        return;

    onStateChanged(QScroller::Pressed);
    hScrollBarValueChanged(1);
    pageIndex = page;
    onCurrentPageIndexChanged(page);
    onStateChanged(QScroller::Inactive);
    inportFlag = false;
}

//用于根据当前页把对应的点变亮
void SlidePage::onCurrentPageIndexChanged(int index)
{
    for (int i = 0; i < pageIndicator.count(); i++) { 
        if (i == index) // 如果访问的页数是当前页
            pageIndicator[i]->setPixmap(QPixmap(":/icons/indicator2.png")); // 把下面那个点点变亮
        else  // 否则
            pageIndicator[i]->setPixmap(QPixmap(":/icons/indicator1.png")); // 变暗
    }
}


