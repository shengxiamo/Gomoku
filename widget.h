#ifndef WIDGET_H
#define WIDGET_H

#include "gamewidget.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override; // 重写paintEvent函数

private slots:
    void on_playersButton_clicked();

    void on_AIButton_clicked();

private:
    Ui::Widget *ui;
    gameWidget *game;
    QPixmap background; // 声明一个QPixmap对象用于存储背景图片
};

#endif // WIDGET_H
