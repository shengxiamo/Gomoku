#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    game = new gameWidget;
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

