#ifndef WIDGET_H
#define WIDGET_H
#include "stone.h"
#include <QWidget>
#include "step.h"
#include <QVector>
#include <QMessageBox>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
//半径
    int _r;
//    棋子数组
    Stone _s[32];
    //选中的棋子
    //画棋子
    QDialog dlg;
    int _selectid;//选中的棋子
    bool _bRedTurn; //
    void drawStone(QPainter &painter,int id);
    //获取中心点的坐标
    QPoint center(int id);
    QPoint center(int x,int y);
//获取鼠标点击的坐标 最小为（0，0） 最大为（8，9）
    bool getRowCol(QPoint pt,int &row,int &col);
    void getRowCol(int moveid,int &row,int &col);
    //p判断棋子能不能走
    //获取棋子的id 错误返回-1
    int getStoneId(int row,int col);
    int relation(int sRow,int sCol,int dRow,int dCol);
    bool canMove(int moveid,int row,int col,int killid);
    bool canMoveCHE(int moveid,int row,int col,int killid);
    bool canMoveMA(int moveid,int row,int col,int killid);
    bool canMoveXIANG(int moveid,int row,int col,int killid);
    bool canMoveSHI(int moveid,int row,int col,int killid);
    bool canMoveJIANG(int moveid,int row,int col,int killid);
    bool canMovePAO(int moveid,int row,int col,int killid);
    bool canMoveBING(int moveid,int row,int col,int killid);

    void moveStone(int moveid, int row, int col);
    void moveStone(int moveid, int row, int col,int killid);
    int getStoneAtLine(int sRow,int sCol,int dRow,int dCol);
//绘图和鼠标事件
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *ev);



    int _level;
    void saveStep(int moveid,int killid,int row,int col,QVector<Step *> &steps);
    void getAllPossinleMove(QVector<Step *>&steps);
    int score();
    Step *getBestMove();
    void fakeMove(Step *step);
    void unfakeMove(Step *step);
    void computerMove();

//    int getMinScore(int level, int curMin);
//    int getMaxScore(int level,int curMax);

};

#endif // WIDGET_H
