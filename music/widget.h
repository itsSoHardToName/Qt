#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
namespace Ui {
class Widget;
}
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QListWidget>
#include <QSlider>
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void setSheet();
private slots:
    void on_listBtn_clicked();

    void on_playBtn_clicked();

    void on_sortBtn_clicked();

    void on_previousBtn_clicked();

    void on_nextBtn_clicked();
    void k(int row);
    void metaDataAvailableChanged(bool available);
    void moveEvent(QMoveEvent *event);
    void setSliderSt();
    void on_soundBtn_clicked();
    void soundValueChange(int value);

private:
    Ui::Widget *ui;
    bool isClicked;
    bool isSoundedbtn;
    bool isPlay;
    QPoint tempPos;
    QMediaPlayer *player;
    QMediaPlaylist *playList;
    QDir dir;
    QListWidget list;
    QSlider slider;
};

#endif // WIDGET_H
