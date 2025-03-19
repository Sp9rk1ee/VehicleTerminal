#ifndef JIEMIAN_H
#define JIEMIAN_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMouseEvent>

#include "icm20608.h"

namespace Ui {
class JieMian;
}

class JieMian : public QWidget
{
    Q_OBJECT

public:
    explicit JieMian(QWidget *parent = nullptr);
    ~JieMian();

protected:
    bool eventFilter(QObject *watch,QEvent *evn) override;

private slots:
    void getICM20608Data();      // 获取数据
private:
    Ui::JieMian *ui;
    ICM20608 *icm20608;
};

#endif // JIEMIAN_H
