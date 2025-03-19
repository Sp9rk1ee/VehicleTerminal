#ifndef LED_H
#define LED_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>

class Led : public QWidget
{
    Q_OBJECT

public:
    Led(QWidget *parent = nullptr);
    ~Led();

    void on_beep_clicked(bool checked);
    void on_led_clicked(bool checked);

private:
    QFile fileled;
    QFile filebeep;
};
#endif // LED_H
