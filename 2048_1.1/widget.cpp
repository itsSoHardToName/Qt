#include "widget.h"
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#define cout qDebug()<<__LINE__
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    score=0;
    labelTitle=new QLabel(this);
    labelScore=new QLabel(this);
    setAutoFillBackground(true);
    setPalette(QColor("#F5F5DC"));
    init(array);
    r=80;
    labelTitle->setText("经典2048");

    labelTitle->move(r,30);
    labelScore->move(r,r*6);
    labelScore->setStyleSheet("Color:#CCC0B2");
    labelScore->setFont(QFont("family",30,700));
    labelScore->resize(QSize(300,r/2));
    labelScore->setText("分数:"+QString::number(score));
    labelTitle->setStyleSheet("Color:#CCC0B2");
    labelTitle->setFont(QFont("family",30,700));
    setFixedSize(530,600);
    setWindowTitle("2048");
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));//初始化随机种子
    randMode();//随机生成2
    randMode();
    setFocusPolicy(Qt::TabFocus);//用来获取焦点
    newBtn=new QPushButton("new game",this);
    newBtn->move(r*4-10,30);
    newBtn->resize(QSize(140,r/2));
    newBtn->setStyleSheet("background-color:#CCC0B2");
    connect(newBtn,&QPushButton::clicked,this,&Widget::startGame);
}

void Widget::startGame()
{
  init(array);
  randMode();//随机生成2
  randMode();
  update();
}


Widget::~Widget()
{

}


//初始化函数
void Widget::init(int array[][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            array[i][j]=0;
        }
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    int val=10;//大方块的间距*5
    int x=0;//方块之间的间距
    int y=0;//方块之间的间距
    QPainter p(this);
    //color CCC0B2
    //ground =187,173,160   0 =204,192,178
    //2 =238,228,218 4 =236,224,200
    //8 =242,177,121 32 =249,124,94
    //128 =37,197,63
    p.setFont(QFont("family", r/4, 300));//设置字体大小

    p.setPen(QColor(187,173,160));
    p.setBrush(QColor(187,173,160));//画刷和字体颜色统一
    p.drawRect(r,r,(r*4)+(val*5),(r*4)+(val*5));//画大方块

    p.setBrush(QColor(204,192,178));
    for(int i=1;i<=4;i++)
    {
        y=0;
        for(int j=1;j<=4;j++)
        {
            int result=array[j-1][i-1];
                //画小方块
            switch (result)
            {
                   case 0:
                        p.setPen(QColor(204,192,178));
                        p.setBrush(QColor(204,192,178));
                        p.drawRect(i*r+val+x,j*r+val+y,r,r);
                        break;
                    case 2:
                        p.setPen(QColor(238,228,218));
                        p.setBrush(QColor(238,228,218));
                        p.drawRect(i*r+val+x,j*r+val+y,r,r);
                        break;
                case 4:
                p.setPen(QColor(236,224,200));
                    p.setBrush(QColor(236,224,200));
                    p.drawRect(i*r+val+x,j*r+val+y,r,r);
                    break;
                case 8:
                case 16:
                p.setPen(QColor(242,177,121));
                    p.setBrush(QColor(242,177,121));
                    p.drawRect(i*r+val+x,j*r+val+y,r,r);
                    break;
                case 32:
                case 64:
                p.setPen(QColor(249,124,94));
                    p.setBrush(QColor(249,124,94));
                    p.drawRect(i*r+val+x,j*r+val+y,r,r);
                default:
                    p.setPen(QColor(37,197,63));
                    p.setBrush(QColor(37,197,63));
                    p.drawRect(i*r+val+x,j*r+val+y,r,r);
                    break;
            }

                p.setPen(QColor(0,0,64));
                if(array[j-1][i-1]!=0)
                p.drawText(QRect(i*r+val+x,j*r+val+y,r,r),QString::number(array[j-1][i-1]),QTextOption(Qt::AlignCenter));//画字体

            y+=10;
        }
        x+=10;
    }
}

void Widget::leftmerge(int array[][N])
{
    for(int i=0;i<N;i++)
      {
        for(int j=1;j<4;)
        {
            if(array[i][j]==array[i][j-1])
            {
                array[i][j-1]=(array[i][j])*2;
                 score+=array[i][j]*2;
                labelScore->setText("分数:"+QString::number(score));
                array[i][j]=0;
                j+=2;
            }else
            {
                j++;
            }
        }
    }

}

void Widget::rightmerge(int array[][N])
{
    for(int i=N-1;i>=0;i--)
    {
        for(int j=N-2;j>=0;)
        {
            if(array[i][j]==array[i][j+1])
            {
                array[i][j+1]=array[i][j]*2;
                score+=array[i][j]*2;
                labelScore->setText("分数:"+QString::number(score));
                array[i][j]=0;
                j-=2;
            }else
            {
                j--;
            }
        }
    }
}

void Widget::upmerge(int array[][N])
{
    for(int j=0;j<N;j++)
    {
        for(int i=1;i<N;)
        {
            if(array[i][j]==array[i-1][j])
            {
                array[i-1][j]=array[i][j]*2;
                score+=array[i][j]*2;
                labelScore->setText("分数:"+QString::number(score));
                array[i][j]=0;
                i+=2;
            }else
            {
                i++;
            }
        }
    }
}

void Widget::downmerge(int array[][N])
{
    for(int j=N-1;j>=0;j--)
    {
        for(int i=N-2;i>=0;)
        {
            if(array[i][j]==array[i+1][j])
            {
                array[i+1][j]=array[i][j]*2;
                score+=array[i][j]*2;
                labelScore->setText("分数:"+QString::number(score));
                array[i][j]=0;
                i-=2;;
            }
            i--;
        }
    }
}

void Widget::isDie(int array[][N])
{
   int x=0,y=0;
        for(int i=0;i<4;i++)
        {
                if(array[i][0]!=array[i][1]&&array[i][1]!=array[i][2]&&array[i][2]!=array[i][3])
                {
                     x++;
                }
        }
        for(int j=0;j<4;j++)
        {
            if(array[0][j]!=array[1][j]&&array[1][j]!=array[2][j]&&array[2][j]!=array[3][j])
            {             
                y++;
            }
        }
        int btn;
        if(x==4&&y==4)
           btn =QMessageBox::information(this,"提示","游戏结束,是否要重来一局",
                                    QMessageBox::Yes,QMessageBox::No);
        if(btn==QMessageBox::Yes)//standard button return value
        {
            startGame();
        }
}


void Widget::randMode()
{
    int x,y;
    bool status=true;//
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(array[i][j]==0)
                {
                    status=false;
                }
            }
        }
        if(status)
        {
            isDie(array);
        }else
        {
             while(array[x=qrand()%4][y=rand()%4]!=0);
             array[x][y]=2;
        }
}


void Widget::upMove(int array[][N])
{
    for(int j=0;j<N;j++)
        {
            for(int i=0;i<N;i++)
            {
                if(array[i][j]==0)
                {
                    for(int k=i+1;k<N;k++)
                    {
                        if(array[k][j]==0)continue;
                        else
                        {
                            int temp=array[i][j];
                            array[i][j]=array[k][j];
                            array[k][j]=temp;
                            break;
                        }
                    }
                }
            }
        }

}

void Widget::downMove(int array[][N])
{
    for(int j=N-1;j>=0;j--)
    {
            for(int i=N-1;i>=0;i--)
            {
                if(array[i][j]==0)
                {
                    for(int k=i-1;k>=0;k--)
                    {
                        if(array[k][j]==0)continue;
                        else
                        {
                            int temp=array[i][j];
                            array[i][j]=array[k][j];
                            array[k][j]=temp;
                            break;
                        }
                    }
                }
            }
    }
}

void Widget::leftMove(int array[][N])
{
    for(int i=0;i<N;i++)
    {
            for(int j=0;j<N;j++)
            {
                if(array[i][j]==0)
                {
                    for(int k=j+1;k<N;k++)
                    {
                        if(array[i][k]==0)continue;
                        else
                        {
                            int temp=array[i][j];
                            array[i][j]=array[i][k];
                            array[i][k]=temp;
                            break;
                        }
                    }
                }
            }
    }
}

void Widget::rightMove(int array[][N])
{
    for(int i=N-1;i>=0;i--)
        {
            for(int j=N-1;j>=0;j--)
            {
                if(array[i][j]==0)
                {
                    for(int k=j-1;k>=0;k--)
                    {
                        if(array[i][k]==0)continue;
                        else
                        {
                            int temp=array[i][j];
                            array[i][j]=array[i][k];
                            array[i][k]=temp;
                            break;
                        }
                    }
                }
            }
        }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        upMove(array);
        upmerge(array);
        upMove(array);
        randMode();
        update();
            break;
    case Qt::Key_Down:
        downMove(array);
        downmerge(array);
        downMove(array);
        randMode();
        update();
            break;
    case Qt::Key_Left:
        leftMove(array);
        leftmerge(array);
        leftMove(array);
        randMode();
        update();
            break;
    case Qt::Key_Right:
        rightMove(array);
        rightmerge(array);
        rightMove(array);
        randMode();
        update();
            break;
    default:
        return ;
    }
}



