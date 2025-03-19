#ifndef PITHERBIG_H
#define PITHERBIG_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>

namespace Ui {
class PitherBig;
}

class PitherBig : public QWidget
{
    Q_OBJECT

public:
    explicit PitherBig(QWidget *parent = nullptr);
    ~PitherBig();
    void showPixmap(QPixmap);
    void getPixmapData(QPixmap);
private slots:
    void on_pushButton_left1(bool);
    void on_pushButton_right1(bool);

private:
    void mousePressEvent(QMouseEvent *event);

signals:
    void hide_();
private:
    Ui::PitherBig *ui;
    QVector<QPixmap> pixmapData;
    QPushButton *pushButton_left;
    QPushButton *pushButton_right;
    QTimer *timerdoubleClock;
    int item_number;
};

#endif // PITHERBIG_H
