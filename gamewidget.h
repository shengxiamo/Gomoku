#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "chessai.h"
#include "chessai.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

namespace Ui {
class gameWidget;
}

class gameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit gameWidget(QWidget *parent = nullptr);
    ~gameWidget();
    void oneChessMove(int row,int col);// 根据落子坐标更新棋局状态
    bool chessOneByPlayer();
    void initializeGame(); // 重新开始
    bool isDeadGame();//判断是否是僵局
    bool deadWindow(QMessageBox *msg);
    QMessageBox msg;
    void setGameMode(gameMode m){mode=m;}
private:
    Ui::gameWidget *ui;
    QPoint chessboard[15][15];// 记录棋盘角点坐标，方便绘制棋盘,第一个下标是列，第二个是行

    chessAI ai;//棋盘放在ai当中

    int cursorRow;// 获取当前光标位置，用于落子定位
    int cursorCol;

    int lastRow;
    int lastCol;
    // 记录已经下过的子的位置，便于悔棋

    int usedChesses[15][15];

    gameMode mode =NONE;
    gameTurn turn;
    gameStatus status;
    bool is_in_chessboard = false;  // 优化点，增加一个属性，与鼠标事件结合实时检测鼠标是否在棋盘内

    int score_black;
    int score_white;
    int numOfChess;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;//实际落子
private slots:
    void on_restartButton_clicked();
};


#endif // GAMEWIDGET_H
