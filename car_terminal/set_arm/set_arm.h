#ifndef SET_ARM_H
#define SET_ARM_H

#include <QWidget>
#include <QFile>
#include <QDir>
#include <QLabel>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Set_arm; }
QT_END_NAMESPACE

class Set_arm : public QWidget
{
    Q_OBJECT

public:
    Set_arm(QWidget *parent = nullptr);
    ~Set_arm();

private slots:
    void on_pushButton_wallpaper_clicked();

    void on_pushButton_use_text_clicked();

signals:
    void bizi_path(QString);
    void use_name(bool);
private:
    Ui::Set_arm *ui;
    QLabel *setting;
    QStringList bizi_path_list;
    int bizi_number;
    bool use_name_;
};
#endif // SET_ARM_H
