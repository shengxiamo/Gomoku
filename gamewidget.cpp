#include "gamewidget.h"
#include "ui_gamewidget.h"

gameWidget::gameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gameWidget)
{
    ui->setupUi(this);
    for(int i = 0;i < 15;++i){// 棋盘左上角点为(20,20),每格间距为40
        for(int j = 0;j < 15;++j){
            chessboard[i][j].setX(20 + 40 * i);
            chessboard[i][j].setY(20 + 40 * j);
            ai.chesses[i][j] = 0;
        }
    }

    setMouseTracking(true);// 不用点击鼠标也一直追踪
}

gameWidget::~gameWidget()
{
    delete ui;
}

void gameWidget::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //绘制棋盘
    painter.setPen(Qt::black);
    for(int i = 0;i < 15;++i){
        painter.drawLine(chessboard[0][i],chessboard[14][i]);
        painter.drawLine(chessboard[i][0],chessboard[i][14]);
    }

    if(turn == T_BLACK) {  // 黑方落子
        painter.setBrush(Qt::black);
    }
    else {
        painter.setBrush(Qt::white);
    }

    // 画鼠标光标
    if(cursorRow != -1 && cursorCol != -1 && is_in_chessboard){ // 鼠标在棋盘范围内
        // 在角点处绘制边长为8的矩形
        QRect rec(chessboard[cursorCol][cursorRow].x() - 8 / 2,chessboard[cursorCol][cursorRow].y() -8 / 2,8,8);
        painter.drawRect(rec);
    }
    // //qDebug()<<"你亲爹的状态（画棋子之前）"<<ai.chesses[0][0];

    // 绘制棋子
    for(int i = 0;i < 15;++i){
        for(int j = 0;j < 15;++j){
            if(ai.chesses[i][j] != C_NONE && ai.myChesses[i][j] != 0){  // 该点不为空
                if(ai.chesses[i][j] == C_BLACK || ai.myChesses[i][j] % 2==1){ // 黑方落子，模二的原因是AI对战玩家始终在奇数步落子
                    painter.setBrush(Qt::black);
                    ai.chesses[i][j] = C_BLACK; // ？可能有chess为白但其实是黑子的情况吗？  AI落子时未更新chess？
                }
                else {painter.setBrush(Qt::white);
                    ai.chesses[i][j] = C_WHITE;
                }

    //             // 判断是否为最后一颗棋子
    //             //产生了一个bug，所有在最后一颗子下方的棋子会被红圈包围
    //             //原因是棋子会按顺序遍历，从0，0到14，14.如果在前面的棋子是last one
    //             //那么画笔的颜色就会被改成红色，于是接下来每一个给棋子描边的画笔都是红色
    //             //只需要在标记the last one之后把红色改回即可
                if (i == lastRow && j == lastCol) {
                    painter.drawEllipse(chessboard[j][i].x() - 30 / 2, chessboard[j][i].y() - 30 / 2, 30, 30);
                    painter.setPen(QPen(Qt::red, 2, Qt::SolidLine)); // 设置画笔
                    // 最后一颗棋子用红色十字线标记
                    painter.drawLine(chessboard[j][i].x() - 15, chessboard[j][i].y(), chessboard[j][i].x() + 15, chessboard[j][i].y());
                    painter.drawLine(chessboard[j][i].x(), chessboard[j][i].y() - 15, chessboard[j][i].x(), chessboard[j][i].y() + 15);
    //                 //试图纠正红圈Bug
    //                 //把画笔调回默认情况下的黑色就可以解决
                    painter.setPen(QPen(Qt::black));
                }
                else {
                    painter.drawEllipse(chessboard[j][i].x() - 30 / 2, chessboard[j][i].y() - 30 / 2, 30, 30);// 画一个半径为30的圆表示棋子
                }
            }
        }
    }
    // //qDebug()<<"你亲爹的状态（画棋子之后）"<<ai.chesses[0][0];
}

void gameWidget::mouseMoveEvent(QMouseEvent *event){
    //判断鼠标是否在棋盘内
    if(event->x() >= 0 && event->x() <= 600 && event->y() >= 0 && event->y() <= 600){  // 0 = 20 -20 = 600 = 14 * 40 + 20 + 20 确保边界判定范围不变,仍为 40 * 40
        is_in_chessboard = true;  // 优化1：在确认落子前确定“当前”的鼠标位置仍然在棋盘内，否则不落子
        // 如果在棋盘内，则把鼠标设置为空白
        setCursor(Qt::BlankCursor);
        // for(int i=0;i<15;++i)
        //     for(int j=0;j<15;++j){
        //         //鼠标位置
        //         float x=event->x(),y=event->y();
        //         //判断鼠标落在哪一个点附近(正方形范围)
        //         if((x >= (chessboard[i][j].x() - 20)) && (x < (chessboard[i][j].x() + 20)) &&
        //             (y >= (chessboard[i][j].y() - 20))&&(y < (chessboard[i][j].y() + 20))) {
        //             cursorRow = j;
        //             cursorCol = i;

        // 优化2：直接将鼠标坐标映射为棋盘坐标，虽然都是O（1）时间复杂度，但是不需要重复255次循环，速度提高上百倍，用户体验明显流畅
        cursorCol = (event->x()) / 40;
        cursorRow = (event->y()) / 40;
                    //如果该点有子，则显示红圈
                    if(ai.chesses[cursorRow][cursorCol] != C_NONE)
                        setCursor(Qt::ForbiddenCursor);

                    //展示图标坐标
                    QString str = "坐标:";
                    str += QString::number(cursorCol);
                    str += ",";
                    str += QString::number(cursorRow);
                    if(turn == T_BLACK) ui->lb_black_position->setText(str);
                    else ui->lb_white_position->setText(str);
                    // break;
                //}
            //}
    }
    //如果在棋盘外，显示鼠标
    else {
        setCursor(Qt::ArrowCursor);
        is_in_chessboard = false;
    }
    update();
}

// 实现落子的功能
void gameWidget::oneChessMove(int row, int col){
    numOfChess++;
    usedChesses[row][col]=numOfChess;
    //将棋谱传递给算法文件
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            ai.myChesses[i][j]=usedChesses[i][j];
        }
    }
    qDebug()<<row<<","<<col;
    // 如果上一步是黑棋下的，记录位置，把下一步棋交给白棋，反之亦然
    if(turn==T_BLACK){
        turn=T_WHITE;
        ai.chesses[row][col]=C_BLACK;
    }
    else{
        turn=T_BLACK;
        ai.chesses[row][col]=C_WHITE;
    }
    //如果这步棋下完之后游戏结束，则更改游戏状态
     gameResult result=ai.evaluate(ai.chesses).result;
    if(result!=R_DRAW ||isDeadGame()) status=FINISH;

    update();
}

// 玩家下棋
bool gameWidget::chessOneByPlayer(){
    if(ai.chesses[cursorRow][cursorCol]==C_NONE){
        qDebug()<<"player chess";
        oneChessMove(cursorRow,cursorCol);
        //记录最新一步的落子位置
        lastCol=cursorCol;
        lastRow=cursorRow;
        // qDebug()<<"局势得分:"<<ai.evaluate(ai.chesses).score;

        return true;
    }
    return false;
}

void gameWidget::mouseReleaseEvent(QMouseEvent *event){ // 玩家点击鼠标左键确认落子
    if((is_in_chessboard || status == FINISH) && mode==PLAYER){
        if(chessOneByPlayer()){
            if(status==FINISH){
                bool newgame=deadWindow(&msg);
                if(newgame) initializeGame();
            }
        }
    }
    else {
        if(chessOneByPlayer()){
            if(status==UNDERWAY){
    //             chessOneByAi();
    //             if(status==FINISH){
    //                 bool newgame=deadWindow(&msg);
    //                 if(newgame)
    //                     initializeGame();
    //             }
    //         }
    //         else if(status==FINISH){
    //             bool newgame=deadWindow(&msg);
    //             if(newgame)
    //                 initializeGame();
            }
        }
    }
}

void gameWidget::initializeGame(){

    int static count=0;
    qDebug()<<"游戏第"<<count<<"次初始化";
    if(mode==PLAYER)qDebug()<<"上一次游玩的是玩家模式";
    else if(mode==AI) qDebug()<<"上一次游玩的是人机模式";
    else if(mode==NONE) qDebug()<<"无模式";
    //ai.zobb.initRandomTable();
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            ai.chesses[i][j]=C_NONE;
            usedChesses[i][j]=0;
        }
    }

    status=UNDERWAY;
    turn=T_BLACK;
    cursorRow=-1;
    cursorCol=-1;
    count++;
    numOfChess=0;
}

void gameWidget::on_restartButton_clicked()
{
    this->hide();
    initializeGame();
    this->show(); //关闭并重新渲染一遍
}

bool gameWidget::isDeadGame(){
    int chessNum=0;
    for(int i=0;i<15;++i)
        for(int j=0;j<15;++j)
            if(ai.chesses[i][j]!=C_NONE)chessNum++;
    if(chessNum==15*15)return true;
    else return false;
}

//游戏结束窗口
bool gameWidget::deadWindow(QMessageBox *msg){
    int static myCount=0;
    msg->setIcon(QMessageBox::Critical);
    if(myCount==0){
        msg->addButton(QMessageBox::Yes);
        msg->addButton(QMessageBox::No);
    }

    gameResult result=ai.evaluate(ai.chesses).result;
    if(result!=R_DRAW) status=FINISH;
    if(result==R_BLACK){
        qDebug()<<"黑棋赢";
        msg->setText("黑棋赢\n想开始下一局吗？");
        score_black++;
    }
    else if(result==R_WHITE){
        qDebug()<<"白棋赢";
        msg->setText("白棋赢\n想开始下一局吗？");
        score_white++;
    }
    else{
        qDebug()<<"平局";
        msg->setText("平局\n想开始下一局吗？");
    }
    ui->lcd_black->display(score_black);
    ui->lcd_white->display(score_white);
    int cliResult = msg->exec();
    myCount++;
    if (cliResult == QMessageBox::Yes) {
        // 用户点击了Yes按钮
        // 在这里执行相关操作
        //initializeGame();
        return true;
    } else {
        // 用户点击了No按钮
        // 在这里执行相关操作
        //此处的操作应该是让棋盘删除黑棋和白棋的最后一颗棋子
        return false;
    }

}

