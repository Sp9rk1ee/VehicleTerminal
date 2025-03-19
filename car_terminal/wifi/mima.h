#ifndef MIMA_H
#define MIMA_H

#include <QDialog>
#include "softkeyboard/softkeyboard.h"

namespace Ui {
class Mima;
}

class Mima : public QDialog
{
    Q_OBJECT

public:
    explicit Mima(QWidget *parent = nullptr,QWidget *parent1 = nullptr);
    ~Mima();

    void getmima(QString wifiName);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void wifimima(QString);

private slots:

    void on_buttonBox_accepted();

private:
    Ui::Mima *ui;
    SoftKeyboard *softKeyboard;
};

#endif // MIMA_H
