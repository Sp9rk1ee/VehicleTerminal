#include "folder.h"
#include "ui_folder.h"

Folder::Folder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Folder)
{
    ui->setupUi(this);

    myListwight = new MyListWidget(ui->widget_catalog);//实例化一个MyListWidget对象，父控件是ui->widget_catalog（通过QTDesigner设计的）
    myListwight->resize(this->width(),this->height()*8/9);//调整它的尺寸

#ifdef Q_OS_LINUX  //根据不同的操作系统设置不同的初始的文件路径
    file_name_current = "/";
#endif
#ifdef Q_OS_WIN32
    file_name_current = "D:/laosirangxiazai/QT/tra";
#endif

    readfile();
    //当在 myListwight 中点击一个列表项时，itemClicked 信号会被触发
    connect(myListwight,&MyListWidget::itemClicked,this,&Folder::on_listWidget_itemClicked);
}

Folder::~Folder()
{
    delete ui;
}

//作用是读取当前指定路径（file_name_current）中的文件和文件夹，并将它们显示在 MyListWidget 控件中。
void Folder::readfile()
{
    // 路径栏是否添加
    bool unique = true;// 标志变量，假设 `file_name_current` 目前是唯一的
    for (int i = 0; i < ui->comboBox_site->count(); ++i) {// 遍历 `comboBox_site` 中的所有已有项
        if(file_name_current == ui->comboBox_site->itemText(i))// 如果 `file_name_current` 已经存在于 `comboBox_site` 里
            unique = false;// 说明不是唯一的
    }
    if(unique)//如果 unique == true，说明 file_name_current 还不在 comboBox_site 里，所以使用 addItem() 将其添加进去。
        ui->comboBox_site->addItem(file_name_current);
    ui->comboBox_site->setCurrentText(file_name_current);//把 comboBox_site 里当前选中的文本设置为 file_name_current


    //上面的那些代码主要负责combobox_site里面的显示，和下面的无关，下面的是真正负责显示一个一个文件或文件夹的


    myListwight->clear();  // 清除上一次显示数据
    listwadget_text.clear();//listwadget_text 可能是一个 QStringList，用于存储当前目录下的文件名

    QDir dir(file_name_current);//QDir 是 Qt 提供的目录操作类。这行代码创建一个 QDir 实例，代表 file_name_current 指向的目录。
    QDir dirbsolutePath(dir.absolutePath());//获取 file_name_current 的绝对路径
    // 目录存在？
    if(!dirbsolutePath.exists())
    {
        qDebug()<<"文件夹目录不存在";
        return;
    }

    QStringList files = dirbsolutePath.entryList();//返回该目录下的所有文件和文件夹的名称（字符串列表）

    //ui->listWidget->addItems(files);  // 添加
    for(int i = 0; i< files.count(); i++)
    {
        QString fileNme = files.at(i);//QString::fromUtf8(files.at(i).fileName().toUtf8().data());第i个文件或文件夹的名称
        listwadget_text.append(fileNme);//将fileNme添加到 listwadget_text 里，以便后续使用。

        QWidget *itemWidget = new QWidget(myListwight);
        QGridLayout *itemLayout = new QGridLayout;//itemLayout 是 网格布局，用于排列 QWidget 内部的控件。
        QHBoxLayout *itemContentLayout = new QHBoxLayout;//itemContentLayout 是 水平布局，用于水平排列 图标 (QLabel) 和文件名 (QLabel)。
        QLabel *lblPicture = new QLabel("");//lblPicture 是 用于显示文件/文件夹图标的 QLabel
        QPixmap icon;//icon 是 QPixmap 类型的图片对象，用于加载文件/文件夹图标
        if(fileNme.contains("."))                    // 是否包含“.”来判断是否是文件，从而加载不同图标
            icon.load(":/img/other_file.png.png");   // 包含(文档)
        else
            icon.load(":/img/folder.png");
        lblPicture->setPixmap(icon);//设置前面的icon为要显示的图片
        QLabel *lblContent = new QLabel(fileNme);//lblContent 是一个 QLabel，用于显示文件或文件夹的名称。它的文本内容是 fileNme
        itemContentLayout->addWidget(lblPicture,1);   // itemContentLayout 是一个 QHBoxLayout（水平布局），用于水平排列控件,图片控件占1列
        itemContentLayout->addWidget(lblContent,20);  // 文字占7列
        //itemLayout->addWidget(new QLabel(),1,1,1,5);
        /*这里将 itemContentLayout（包含图标和文字）添加到 itemLayout 中。
        1,6,50,10 是 addLayout 的参数：1：起始行,  6：起始列,  50：跨越的行数,  10：跨越的列数*/
        itemLayout->addLayout(itemContentLayout,1,6,50,10);
        //itemLayout->addWidget(new QLabel(),1,17,1,7);
        itemWidget->setLayout(itemLayout);//把 itemLayout 设为 itemWidget 的布局，即 整个列表项的 UI 结构
        QListWidgetItem *item = new QListWidgetItem(myListwight);//这行代码的作用是在 QListWidget（myListwight）中创建一个新的 QListWidgetItem。
        item->setSizeHint(QSize(54,54));//设置 QListWidgetItem 的尺寸
        myListwight->setItemWidget(item,itemWidget);//这行代码的作用是在 QListWidget 的 item 位置上，显示 itemWidget 这个 QWidget
    }
    myListwight->takeItem(1);//从 QListWidget（myListwight）中移除指定索引的 QListWidgetItem。
    myListwight->takeItem(0);
}

//槽函数，用于处理 QComboBox（下拉框）被用户选中某一项时的操作
void Folder::on_comboBox_site_activated(int index)
{
    file_name_current = ui->comboBox_site->itemText(index);//获取当前选中的文件路径
    readfile();//根据新的文件路径重新显示文件

    for (int i = 0; i <= ui->comboBox_site->count(); ++i) { // 删除index+1之后的项
        if(i > index + 1)
            ui->comboBox_site->removeItem(i);
    }
}

//槽函数，当显示的文件或文件夹被点击时触发
void Folder::on_listWidget_itemClicked(QListWidgetItem *item)
{
    file_name_current = file_name_current + "/" + listwadget_text[myListwight->row(item) + 2];//获取新的路径
    readfile();//重新加载新的文件
}

//当刷新按钮被点击时触发的槽函数
void Folder::on_pushButton_flush_clicked()
{
    readfile();
}

//当comboBox_site旁边的下一项按钮被点击时
void Folder::on_pushButton_next_clicked()
{
    int next = ui->comboBox_site->currentIndex() + 1;//获取comboBox_site里的下一项
    if(ui->comboBox_site->count() > next)
    {
        on_comboBox_site_activated(next);//触发这个槽函数，去更新要显示的文件
        file_name_current = ui->comboBox_site->itemText(next);//更新路径
    }
}

//和上面类似，只不过是前一项
void Folder::on_pushButton_prev_clicked()
{
    int prev = ui->comboBox_site->currentIndex() - 1;
    if(prev >= 0)
    {
        on_comboBox_site_activated(prev);
        file_name_current = ui->comboBox_site->itemText(prev);
    }
}
