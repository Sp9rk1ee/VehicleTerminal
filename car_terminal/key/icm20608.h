#ifndef ICM20608_H
#define ICM20608_H

#include <QObject>
#include <QTimer>

class ICM20608 : public QObject
{
    Q_OBJECT

public:
    explicit ICM20608(QObject *parent = nullptr);
    ~ICM20608();

    QString gxData();
    QString gyData();
    QString gzData();
    QString axData();
    QString ayData();
    QString azData();
    QString tempData();

signals:
    void icm20608DataChanged();

private:
    void icm20608ReadData();

public slots:
    void timer_timeout();

private:
    QTimer *timerr;
    QString gxdata;
    QString gydata;
    QString gzdata;
    QString axdata;
    QString aydata;
    QString azdata;
    QString tempdata;
};

#endif // ICM20608_H
