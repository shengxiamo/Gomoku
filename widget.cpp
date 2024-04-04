#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    game = new gameWidget;
    connect(game,&gameWidget::returnSignal,this,&Widget::show);
    this->setWindowTitle("西大五子棋");
    background = QPixmap(":/images/ganyu.jpg");
}

void Widget::paintEvent(QPaintEvent *event)
{
    // 调用父类的paintEvent函数以确保已经绘制了已存在的内容
    QWidget::paintEvent(event);

    // 创建QPainter对象
    QPainter painter(this);

    // 绘制背景图片
    painter.drawPixmap(0, 0, width(), height(), background);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_playersButton_clicked()
{
    this->hide();
    game->show();
    game->setGameMode(PLAYER);
}

void Widget::on_AIButton_clicked()
{
    this->hide();
    game->show();
    game->setGameMode(AI);
}


