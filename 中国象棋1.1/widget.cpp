#include "widget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#define cout  qDebug()<<"LINE"<<__LINE__<<",FUNC"<<__FUNCTION__
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    _r=30;
    this->resize(600,850);
    for(int i=0;i<32;i++)
        _s[i].init(i);
    _selectid =-1;
    _bRedTurn=true;


}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/image/棋盘.jpg"));
         int d=_r*2;
         //画棋盘 横线
    for(int i=1;i<=10;i++)
    {
        painter.drawLine(QPoint(d,d*i),QPoint(d*9,d*i));
    }
    //竖线
    for(int i=1;i<=9;i++)
    {
        if(i==1||i==9)
        {
            painter.drawLine(QPoint(d*i,d),QPoint(d*i,d*10));
        }
        painter.drawLine(QPoint(d*i,d),QPoint(d*i,d*5));
        painter.drawLine(QPoint(d*i,6*d),QPoint(d*i,d*10));
    }

    //九宫格

   painter.drawLine(QPoint(d*4,d),QPoint(d*6,d*3));
   painter.drawLine(QPoint(d*6,d),QPoint(d*4,d*3));
   painter.drawLine(QPoint(d*6,8*d),QPoint(d*4,d*10));
   painter.drawLine(QPoint(d*4,8*d),QPoint(d*6,d*10));

   //棋子
   for(int i=0;i<32;i++)
   {
       drawStone(painter, i);
   }

}

void Widget::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt=ev->pos();
    //将pt转化为象棋的行列值
    //判断这个行列值有没有棋子
    int row(0),col(0);
    //获取鼠标点击的行列且在棋盘内，返回true  否则返回false
    bool bRet=getRowCol(pt,row,col);
    if(!bRet)
        return ;
    int clickid =-1;//记录点击事件的id
    int i;


    //判断点击事件坐标有没有棋子
    for(i=0;i<32;i++)
    {
        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead==false)
            break;
    }
    //判断是否出了棋盘
    if(i<32)
    {
        clickid=i;
    }

    if(_selectid==-1)
    {
        if(clickid!=-1)
        {//约束 棋子轮流走 bRedTurn=true 红棋走完会反转=false

            if(_bRedTurn==_s[clickid]._red)
            {
                //将点击的值赋给选择的位置，重绘事件
                _selectid=clickid;
                update();

            }
        }
    }
    else
    {
        //判断棋子能不能走
        //_selectid 为选择的棋子，
        //row，col为要走的目标的坐标，不是选中棋子的坐标。
        //clickid 为目标位置的id 如果目标位置没有棋子 则为-1
        if(canMove(_selectid,row,col,clickid))
        {
            moveStone(_selectid,row,col);
            if(clickid!=-1)
            {
                _s[clickid]._dead=true;
            }
            _selectid=-1;

            update();
//            computerMove();
            if(_s[4]._dead)
            {
                QMessageBox::warning(this,"棋局","红方胜利！^_^");
            }
            if(_s[20]._dead)
            {
                QMessageBox::warning(this,"棋局","黑方胜利！……_……");
            }


         }
    }
}



void Widget::drawStone(QPainter &painter, int id)
{

    if(_s[id]._dead)
        return ;
    //获取画字前置条件矩形的位置
    QPoint p=center(id);
    QRect rect(p.x()-_r,p.y()-_r,_r*2,_r*2);

    //初始化笔画刷
    painter.setPen(QPen(Qt::black));
    if(id==_selectid)
        painter.setBrush(Qt::gray);
    else
        painter.setBrush(Qt::white);
    //设置字体风格
    painter.setFont(QFont("family", _r, 700));
    //画红棋
    if(_s[id]._red)
        painter.setPen(QPen(Qt::red));

    //画圆和文本
    painter.drawEllipse(center(id),_r,_r);
    painter.drawText(rect,_s[id].getName(),QTextOption(Qt::AlignCenter));


}


QPoint Widget::center(int id)
{
    return center(_s[id]._row,_s[id]._col);
}

QPoint Widget::center(int x, int y)
{
    QPoint p(((y+1)*_r*2),((x+1)*_r*2));
    return p;

}



bool Widget::getRowCol(QPoint pt, int &row, int &col)
{

    //pt.x /d 得到基本位置  在和x%d 得到的值做比较 就能得到具体的值
    int d=_r*2;
    row=pt.y()/d;
    col=pt.x()/d;
    if(pt.y()%d>=_r)
            row++;
    if(pt.x()%d>=_r)
        col++;
    row--;
    col--;
    if(row<0||row>9||col<0||col>8)
        return false;
    else
        return true;

}

void Widget::getRowCol(int moveid, int &row, int &col)
{
    row=_s[moveid]._row;
    col=_s[moveid]._col;
}

int Widget::getStoneId(int row, int col)
{
    for(int i=0;i<32;i++)
    {
        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead==false)
            return i;
    }
    return -1;
}

void Widget::moveStone(int moveid, int row, int col)
{
    _s[moveid]._row = row;
    _s[moveid]._col = col;

    _bRedTurn = !_bRedTurn;
}

void Widget::moveStone(int moveid, int row, int col, int killid)
{
    _s[killid]._dead=true;
    moveStone(moveid,row,col);
}
int Widget::relation(int sRow, int sCol, int dRow, int dCol)
{
    return qAbs(sRow-dRow)*10+qAbs(sCol-dCol);
}

bool Widget::canMove(int moveid, int row, int col, int killid)
{

    if(killid!=-1)//不用这个判断我的机器就会越界 ……——……
        //判断是不是同色棋子
        if(_s[moveid]._red==_s[killid]._red)
        {
            //如果是同色 就换选中棋子
           _selectid=killid;
           update();
           return false;
        }
    switch (_s[moveid]._type)
    {
    case Stone::CHE:
        return canMoveCHE(moveid,row,col,killid);
    case Stone::MA:
        return  canMoveMA(moveid,row,col,killid);
    case Stone::XIANG:
        return  canMoveXIANG(moveid,row,col,killid);
    case Stone::SHI:
        return canMoveSHI(moveid,row,col,killid);
    case Stone::JIANG:
       return  canMoveJIANG(moveid,row,col,killid);
    case Stone::PAO:
        return canMovePAO(moveid,row,col,killid);
    case Stone::BING:
        return canMoveBING(moveid,row,col,killid);
    };
    return false;

}

bool Widget::canMoveCHE(int moveid, int row, int col, int)
{
    int sRow,sCol;
    getRowCol(moveid,sRow,sCol);  
    int ret =getStoneAtLine(sRow,sCol,row,col);
    if(ret ==0)
        return true;
    return false;
}

bool Widget::canMoveMA(int moveid, int dRow, int dCol, int )
{
    int sRow,sCol;
    //kill 为目标的id 如果目标没有棋子 为-1
    getRowCol(moveid,sRow,sCol);

    int value=relation(sRow,sCol,dRow,dCol);
    if(value!=12&&value!=21)
        return false;
    if(value==12)
    {
        if(getStoneId(sRow,(sCol+dCol)/2)!=-1)
            return false;
    }else
    {
        if(getStoneId((sRow+dRow)/2,sCol)!=-1)
            return false;
    }

    return true;
}

bool Widget::canMoveXIANG(int moveid, int row, int col, int)
{
    int sRow(0),sCol(0);
    getRowCol(moveid,sRow,sCol);

    int val=relation(sRow,sCol,row,col);
    if(val!=22) return false;
    if(getStoneId((sRow+row)/2,(sCol+col)/2)!=-1)//计算象眼
        return false;
    if(!_s[moveid]._red)
    {
        if(row>4) return false;
    }
    else
    {
        if(row<5) return false;
    }

    return true;
}

//做了
bool Widget::canMoveSHI(int moveid, int row, int col, int)
{
    if(!_s[moveid]._red)
    {
        if(row>2) return false;
    }
    else
    {
        if(row<7) return false;
    }

    if(col < 3)return false;
    if(col > 5)return false;

    int val=relation(_s[moveid]._row,_s[moveid]._col,row,col);
    if(val==11)
        return true;
    return false;
}

bool Widget::canMoveJIANG(int moveid, int row, int col, int killid)
{
    // 目标位置 在九宫格内 移动步长为1
    int row1,col1;
    getRowCol(moveid,row1,col1);
    if(_s[moveid]._type==_s[killid]._type&&getStoneAtLine(_s[moveid]._row,_s[moveid]._col,_s[killid]._row,_s[killid]._col)==0)
        return true;
    if(!_s[moveid]._red)
    {
        if(row>2) return false;
    }
    else
    {
        if(row<7) return false;
    }
    if(col<3)return false;
    if(col>5)return false;
    int val=relation(_s[moveid]._row,_s[moveid]._col,row,col);
    if(val==1||val==10)
        return true;

    return false;
}



bool Widget::canMovePAO(int moveid, int row, int col,int)
{
    int sRow,sCol;
    getRowCol(moveid,sRow,sCol);
    int ret =getStoneAtLine(sRow,sCol,row,col);
    if(ret ==0)
    {

        for(int i=0;i<32;i++)
        {
            if(_s[i]._row==row&&_s[i]._col==col)
                return false;
        }
        return true;

    }

    if(ret==1)
    {
        int id=getStoneId(row,col);


       if(id!=-1&&_s[id]._red!=_s[moveid]._red)
           return true;
        else
           return false;
    }
    return false;
}


//搞定
bool Widget::canMoveBING(int moveid, int row, int col, int)
{
    int sRow,sCol;
    getRowCol(moveid,sRow,sCol);
    int val=relation(sRow,sCol,row,col);
    if(val!=1&&val!=10) return false;
    if(_s[moveid]._red)
    {
        if(sRow >=5)
        {
            if(sRow < row) return false;
            if(sCol!=col) return false;
        }else
        {
            if(sRow < row) return false;
        }

    }
    else
    {
        if(sRow<=4)
        {
            if(sRow >row) return false;
            if(sCol!=col) return false;
        }
        else
        {
            if(sRow >row) return false;
        }
    }


    return true;
}

int Widget::getStoneAtLine(int sRow, int sCol, int dRow, int dCol)
{
    int ret =0;
    if(sRow==dRow)
    {
        int min= sCol <dCol ? sCol :dCol;
        int max =sCol <dCol ? dCol :sCol;
        for(int col= min +1;col<max;col ++)
        {
            if(getStoneId(sRow,col)!=-1) ret ++;
        }
        return ret;

    }
    if(sCol==dCol)
    {
        int min=sRow < dRow ? sRow : dRow;
        int max=sRow < dRow ? dRow : sRow;
        for(int row =min+1;row< max;row ++)
        {
            if(getStoneId(row,sCol)!=-1) ++ret;
        }
        return ret;

    }
    return -1;
}








void Widget::saveStep(int moveid,int killid,int row,int col,QVector<Step *> &steps)
{
    int row1,col1;
    getRowCol(moveid,row1,col1);
    Step *step =new Step;
    step->_colFrom=col1;
    step->_rowFrom=row1;
    step->_colTo=col;
    step->_rowTo=row;
    step->_moveid=moveid;
    step->_killid=killid;
    steps.append(step);
}


void Widget::getAllPossinleMove(QVector<Step *> &steps)
{
    for(int i=0;i<16;i++)
    {
        int row,col;
        if(this->_s[i]._dead) continue;
        {
            for(row=0;row<=9;row++)
            {
                for(col=0;col<=8;col++)
                {
                    int killid =this->getStoneId(row,col);
                    if(_s[i]._red==_s[killid]._red&&killid!=-1) continue;

                    if(canMove(i,row,col,killid))
                    {
                        saveStep(i,killid,row,col,steps);
                    }

                }
            }
        }
    }
}


void Widget::fakeMove(Step *step)
{
    _s[step->_killid]._dead=true;
    moveStone(step->_moveid,step->_rowTo,step->_colTo);
}

void Widget::unfakeMove(Step *step)
{
    _s[step->_killid]._dead=false;
    moveStone(step->_moveid,step->_rowFrom,step->_colFrom);
}

void Widget::computerMove()
{
    Step *step=getBestMove();
    cout<<step->_moveid<<step->_rowTo<<step->_colTo<<step->_killid;
    moveStone(step->_moveid,step->_rowTo,step->_colTo,step->_killid);
    delete step;
    update();

}


int Widget::score()
{
    static int s[] = {1000, 499, 501, 200, 15000, 100, 100};
    int scoreBlack=0;
    int scoreRed=0;
    for(int i=0;i<16;i++)
    {
        if(_s[i]._dead) continue;
        scoreBlack+=s[_s[i]._type];
    }
    for(int i=16;i<32;i++)
    {
        if(_s[i]._dead) continue;
        scoreRed+=s[_s[i]._type];
    }
    return scoreBlack-scoreRed;
    
}

Step *Widget::getBestMove()
{
    QVector <Step *> steps;
    getAllPossinleMove(steps);
    Step *ret=NULL;
    int x=0;
    while(steps.count())
    {

        Step *step=steps.last();
        steps.removeLast();
        fakeMove(step);
        int res=score();
        unfakeMove(step);
        if(res>x)
        {
            x=res;
            ret=step;
        }
    }

    return ret;

}
