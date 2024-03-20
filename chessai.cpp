#include "chessai.h"

chessAI::chessAI() {
    init_tuple6type();
}

void chessAI::init_tuple6type(){
    //把六元组的默认值设为0
    memset(tuple6type,0,sizeof (tuple6type));
    //白连5,ai赢
    tuple6type[2][2][2][2][2][2]=WIN;
    tuple6type[2][2][2][2][2][0]=WIN;
    tuple6type[0][2][2][2][2][2]=WIN;
    tuple6type[2][2][2][2][2][1]=WIN;
    tuple6type[1][2][2][2][2][2]=WIN;
    tuple6type[3][2][2][2][2][2]=WIN;//边界考虑
    tuple6type[2][2][2][2][2][3]=WIN;
    //黑连5,ai输
    tuple6type[1][1][1][1][1][1]=LOSE;
    tuple6type[1][1][1][1][1][0]=LOSE;
    tuple6type[0][1][1][1][1][1]=LOSE;
    tuple6type[1][1][1][1][1][2]=LOSE;
    tuple6type[2][1][1][1][1][1]=LOSE;
    tuple6type[3][1][1][1][1][1]=LOSE;
    tuple6type[1][1][1][1][1][3]=LOSE;
    //白活4
    tuple6type[0][2][2][2][2][0]=FLEX4;
    //黑活4
    tuple6type[0][1][1][1][1][0]=flex4;
    //白活3
    tuple6type[0][2][2][2][0][0]=FLEX3;
    tuple6type[0][0][2][2][2][0]=FLEX3;
    tuple6type[0][2][0][2][2][0]=FLEX3;
    tuple6type[0][2][2][0][2][0]=FLEX3;
    //黑活3
    tuple6type[0][1][1][1][0][0]=flex3;
    tuple6type[0][0][1][1][1][0]=flex3;
    tuple6type[0][1][0][1][1][0]=flex3;
    tuple6type[0][1][1][0][1][0]=flex3;
    //白活2
    tuple6type[0][2][2][0][0][0]=FLEX2;
    tuple6type[0][2][0][2][0][0]=FLEX2;
    tuple6type[0][2][0][0][2][0]=FLEX2;
    tuple6type[0][0][2][2][0][0]=FLEX2;
    tuple6type[0][0][2][0][2][0]=FLEX2;
    tuple6type[0][0][0][2][2][0]=FLEX2;
    //黑活2
    tuple6type[0][1][1][0][0][0]=flex2;
    tuple6type[0][1][0][1][0][0]=flex2;
    tuple6type[0][1][0][0][1][0]=flex2;
    tuple6type[0][0][1][1][0][0]=flex2;
    tuple6type[0][0][1][0][1][0]=flex2;
    tuple6type[0][0][0][1][1][0]=flex2;
    //白活1
    tuple6type[0][2][0][0][0][0]=FLEX1;
    tuple6type[0][0][2][0][0][0]=FLEX1;
    tuple6type[0][0][0][2][0][0]=FLEX1;
    tuple6type[0][0][0][0][2][0]=FLEX1;
    //黑活1
    tuple6type[0][1][0][0][0][0]=flex1;
    tuple6type[0][0][1][0][0][0]=flex1;
    tuple6type[0][0][0][1][0][0]=flex1;
    tuple6type[0][0][0][0][1][0]=flex1;

    int p1,p2,p3,p4,p5,p6,x,y,ix,iy;//x:左5中黑个数,y:左5中白个数,ix:右5中黑个数,iy:右5中白个数
    for(p1=0;p1<4;++p1){
        for(p2=0;p2<3;++p2){
            for(p3=0;p3<3;++p3){
                for(p4=0;p4<3;++p4){
                    for(p5=0;p5<3;++p5){
                        for(p6=0;p6<4;++p6){

                            x=y=ix=iy=0;
                            //p1为左，p6为右，其余为中间，所以两个数都自增
                            if(p1==1)x++;
                            else if(p1==2)y++;

                            if(p2==1){x++;ix++;}
                            else if(p2==2){y++;iy++;}

                            if(p3==1){x++;ix++;}
                            else if(p3==2){y++;iy++;}

                            if(p4==1){x++;ix++;}
                            else if(p4==2){y++;iy++;}

                            if(p5==1){x++;ix++;}
                            else if(p5==2){y++;iy++;}

                            if(p6==1)ix++;
                            else if(p6==2)iy++;

                            if(p1==3||p6==3){//有边界
                                if(p1==3&&p6!=3){//左边界
                                    //白冲4
                                    if(ix==0&&iy==4){//若右边有空位是活4也没关系，因为活4权重远大于冲4，再加上冲4权重变化可以不计
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=BLOCK4;
                                    }
                                    //黑冲4
                                    if(ix==4&&iy==0){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=block4;
                                    }
                                    //白眠3
                                    if(ix==0&&iy==3){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=BLOCK3;
                                    }
                                    //黑眠3
                                    if(ix==3&&iy==0){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=block3;
                                    }
                                    //白眠2
                                    if(ix==0&&iy==2){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=BLOCK2;
                                    }
                                    //黑眠2
                                    if(ix==2&&iy==0){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=block2;
                                    }
                                }else if(p6==3&&p1!=3){//右边界
                                    //白冲4
                                    if(x==0&&y==4){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=BLOCK4;
                                    }
                                    //黑冲4
                                    if(x==4&&y==0){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=block4;
                                    }
                                    //黑眠3
                                    if(x==3&&y==0){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=BLOCK3;
                                    }
                                    //白眠3
                                    if(x==0&&y==3){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=block3;
                                    }
                                    //黑眠2
                                    if(x==2&&y==0){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=BLOCK2;
                                    }
                                    //白眠2
                                    if(x==0&&y==2){
                                        if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                            tuple6type[p1][p2][p3][p4][p5][p6]=block2;
                                    }
                                }
                            }else{//无边界
                                //白冲4
                                if((x==0&&y==4)||(ix==0&&iy==4)){
                                    if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                        tuple6type[p1][p2][p3][p4][p5][p6]=BLOCK4;
                                }
                                //黑冲4
                                if((x==4&&y==0)||(ix==4&&iy==0)){
                                    if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                        tuple6type[p1][p2][p3][p4][p5][p6]=block4;
                                }
                                //白眠3
                                if((x==0&&y==3)||(ix==0&&iy==3)){
                                    if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                        tuple6type[p1][p2][p3][p4][p5][p6]=BLOCK3;
                                }
                                //黑眠3
                                if((x==3&&y==0)||(ix==3&&iy==0)){
                                    if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                        tuple6type[p1][p2][p3][p4][p5][p6]=block3;
                                }
                                //白眠2
                                if((x==0&&y==2)||(ix==0&&iy==2)){
                                    if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                        tuple6type[p1][p2][p3][p4][p5][p6]=BLOCK2;
                                }
                                //黑眠2
                                if((x==2&&y==0)||(ix==2&&iy==0)){
                                    if(tuple6type[p1][p2][p3][p4][p5][p6]==0)
                                        tuple6type[p1][p2][p3][p4][p5][p6]=block2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    qDebug() << "六元组初始化完毕";
}

EVALUATION chessAI::evaluate(int board[15][15],bool needPrint) {
    //各棋型权重
    int weight[17]={0,1000000,-10000000,50000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3};

    int i,j,type;
    int stat[4][17];//统计4个方向上每种棋型的个数
    memset(stat,0,sizeof(stat));


    int A[17][17];//包括边界的虚拟大棋盘,board[i][j]=A[i-1][j-1],3表示边界
    for(i=0;i<17;++i){
        A[i][0]=3;
        A[i][16]=3;
    }
    for(j=0;j<17;++j){
        A[0][j]=3;
        A[16][j]=3;
    }
    for(i=0;i<15;++i)
        for(j=0;j<15;++j)
            A[i+1][j+1]=board[i][j];

    // 判断横向棋型
    for(i=1;i<=15;++i){
        for(j=0;j<12;++j){
                type=tuple6type[A[i][j]][A[i][j+1]][A[i][j+2]][A[i][j+3]][A[i][j+4]][A[i][j+5]];
            stat[0][type]++;
        }
    }
    qDebug() << "static raw done";
    //判断竖向棋型
    for(j=1;j<=15;++j){
        for(i=0;i<12;++i){
             qDebug() << "search to"<< i << "*" << j;
            type=tuple6type[A[i][j]][A[i+1][j]][A[i+2][j]][A[i+3][j]][A[i+4][j]][A[i+5][j]];
            stat[1][type]++;
        }
    }
    //判断左上至右下棋型
    for(i=0;i<12;++i){
        for(j=0;j<12;++j){
            type=tuple6type[A[i][j]][A[i+1][j+1]][A[i+2][j+2]][A[i+3][j+3]][A[i+4][j+4]][A[i+5][j+5]];
            stat[2][type]++;
        }
    }
    //判断右上至左下棋型
    for(i=0;i<12;++i){
        for(j=5;j<17;++j){
            type=tuple6type[A[i][j]][A[i+1][j-1]][A[i+2][j-2]][A[i+3][j-3]][A[i+4][j-4]][A[i+5][j-5]];
            stat[3][type]++;
        }
    }

    qDebug() << "static done";
    EVALUATION eval;
    memset(eval.STAT,0,sizeof (eval.STAT));

    int score=0;
    for(i=1;i<17;++i){
        score+=(stat[0][i]+stat[1][i]+stat[2][i]+stat[3][i])*weight[i];//初步计分

        int count=stat[0][i]+stat[1][i]+stat[2][i]+stat[3][i];//统计所有方向上部分棋型的个数
        //统计不同类型，主要是自己的杀棋和正负判断
        if(i==WIN)eval.STAT[WIN]=count;
        else if(i==LOSE)eval.STAT[LOSE]=count;
        else if(i==FLEX4)eval.STAT[FLEX4]=count;
        else if(i==BLOCK4)eval.STAT[BLOCK4]=count;
        else if(i==FLEX3)eval.STAT[FLEX3]=count;
    }

    /* if(needPrint==true){
        qDebug()<<"局面棋型判断";
        for(int i=0;i<17;++i)
            qDebug()<<i<<":"<<STAT[i];
    }
*/
    eval.result=R_DRAW;

    //白赢
    if(eval.STAT[WIN]>0)eval.result=R_WHITE;
    //黑赢
    else if(eval.STAT[LOSE]>0)eval.result=R_BLACK;

    eval.score=score;
    return eval;
}
