#ifndef CHESSAI_H
#define CHESSAI_H

#include <QDebug>
#include <QPoint>

#define EXACT 4
#define ALPHA 1
#define BETA 2
#define KILL 3

#define C_NONE 0//棋子：黑子,白子,无子
#define C_BLACK 1
#define C_WHITE 2

#define RIGHT 0//方向：向右、向上、右上、左上
#define UP 1
#define UPRIGHT 2
#define UPLEFT 3

//各个棋型的代号 /权重
#define OTHER 0//其他棋型
#define WIN 1//1000000,白赢
#define LOSE 2//-10000000
#define FLEX4 3//50000,白活4
#define flex4 4//-100000
#define BLOCK4 5//400
#define block4 6//-100000
#define FLEX3 7//400
#define flex3 8//-8000
#define BLOCK3 9//20
#define block3 10//-40
#define FLEX2 11//20
#define flex2 12//-40
#define BLOCK2 13//1
#define block2 14//-2
#define FLEX1 15//1
#define flex1 16//-2

enum gameMode{PLAYER,AI,NONE}; // 游戏模式

enum gameStatus{UNDERWAY,FINISH}; // 棋局状态

enum gameTurn{T_BLACK,T_WHITE}; // 轮到谁下

enum gameResult{R_BLACK,R_WHITE,R_DRAW}; // 棋局结果：黑棋赢，白棋赢，和棋

struct EVALUATION{
    int score;
    gameResult result;
    int STAT[8]; // 储存部分棋形的个数,下标WIN=1为白连5,LOSE=2为黑连5,FLEX4=3为白活4,BLOCK4=5为白冲4,FLEX3=7为白活3
};

struct POINTS{ // 最佳落子位置,[0]分数最高,[19]分数最低
    QPoint pos[20];
    int score[20]; //此处落子的局势分数
};

struct DECISION{  // AI最终的决定
    QPoint pos; // 位置
    int eval; // 对分数的评估
};
class chessAI
{
public:
    chessAI();
    int chesses[15][15];// 存储整个棋局,0为无子,1为黑子,3为白子
    int myChesses[15][15];// 存储AI对应位置棋子是第几步落下的
};

#endif // CHESSAI_H
