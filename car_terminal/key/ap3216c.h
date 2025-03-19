#ifndef AP3216C_H
#define AP3216C_H

#include <QObject>
#include <QTimer>

class Ap3216c : public QObject
{
    Q_OBJECT
public:
    explicit Ap3216c(QObject *parent = nullptr);
    ~Ap3216c();

    QString alsData(); //  光
    QString psData();  //  距离
    QString irData();  //  红外

signals:
    void ap3216cDataChanged();

private:
    QString readAlsData();
    QString readPsData();
    QString readIrData();

private slots:
    void timer_timeout();

private:
    QTimer *timerr;

    QString alsdata;
    QString psdata;
    QString irdata;

};

#endif // AP3216C_H
