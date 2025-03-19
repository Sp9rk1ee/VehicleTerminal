#ifndef FOLDER_H
#define FOLDER_H

#include <QWidget>
#include <QFile>
#include <QDir>
#include <QTextCodec>
#include <QTextStream>
#include <QListWidgetItem>
#include <QLabel>
#include <QDebug>
#include "mylistwidget.h"

/*************文件夹**************/

QT_BEGIN_NAMESPACE
namespace Ui { class Folder; }
QT_END_NAMESPACE

class Folder : public QWidget
{
    Q_OBJECT

public:
    Folder(QWidget *parent = nullptr);
    ~Folder();

public:
    void readfile();

private slots:
    void on_comboBox_site_activated(int index);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_flush_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_prev_clicked();

private:
    Ui::Folder *ui;
    QVector<QString> listwadget_text;
    QString file_name_current;
    MyListWidget *myListwight;
};
#endif // FOLDER_H
