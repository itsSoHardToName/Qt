#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#define N 4
#include <QPushButton>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    int array[N][N];
    void init(int array[][N]);
    void paintEvent(QPaintEvent *event);
    int r;
    void upMove(int array[][N]);
    void downMove(int array[][N]);
    void leftMove(int array[][N]);
    void rightMove(int array[][N]);
    void keyPressEvent(QKeyEvent *event);
    void leftmerge(int array[][N]);
    void rightmerge(int array[][N]);
    void upmerge(int array[][N]);
    void downmerge(int array[][N]);
    void isDie(int array[][N]);
    void randMode();
    QPushButton *newBtn;
    QPushButton *cloBtn;
    void startGame();
    QLabel *labelTitle;
    QLabel *labelScore;
    int score;


};

#endif // WIDGET_H
