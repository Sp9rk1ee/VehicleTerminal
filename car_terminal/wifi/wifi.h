#ifndef WIFI_H
#define WIFI_H

#include <QWidget>
#include <QDebug>
#include <QProcess> //进程
#include <QFile>
#include <QTimer>
#include <QListWidgetItem>
#include <QEventLoop>
#include <QTimer>
#include "mima.h"
#include "folder/mylistwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Wifi; }
QT_END_NAMESPACE

class Wifi : public QWidget
{
    Q_OBJECT

public:
    Wifi(QWidget *parent = nullptr);
    ~Wifi();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_toggled(bool checked);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void timeOut_timer_judge_wifi();

private:
    void execute_cmd(QString text,QProcess *process);

signals:
    void wifi_judge(bool);
private:
    Ui::Wifi *ui;
    QProcess *process;
    QTimer *timer_joint_wifi;
    QString wifiNamemima;
    Mima *mima;
};
#endif // WIFI_H
