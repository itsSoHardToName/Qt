#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QIcon>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //判断列表是否点击 如果点击则显示列表
    setWindowIcon(QIcon(QPixmap(":/icon/音乐.png")));
    isClicked=true;
    //判断音乐是否播放
    isPlay=true;
        slider.setMinimum(0);
        slider.setMaximum(100);
    //按钮点击
    isSoundedbtn=true;
    //样式表设置
    setSheet();
    setSliderSt();


    //new播放列表和对象
    playList=new QMediaPlaylist(this);
    player=new QMediaPlayer(this);

    slider.setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    slider.setOrientation(Qt::Horizontal);

    //设置当前目录
    dir.setCurrent("D:/CloudMusic");
    //遍历窗口 将目录文件添加到playList
    dir.setFilter(QDir::Files);
    //文件类型过滤
    dir.setNameFilters(QStringList("*.mp3"));
    QList<QString> dirList=dir.entryList();
    foreach (QString str, dirList) {
        playList->addMedia(QUrl::fromLocalFile(tr("D:/CloudMusic/%1").arg(str)));
        list.addItem(str);
//        qDebug()<<"D:/CloudMusic/"+str;
    }
    player->setPlaylist(playList);
    //顺序播放
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    connect(ui->closeBtn,&QPushButton::clicked,this,&Widget::close);
    connect(&list,&QListWidget::currentRowChanged,this,&Widget::k);
    connect(player,&QMediaPlayer::metaDataAvailableChanged,
            this,&Widget::metaDataAvailableChanged);
    connect(&slider,&QSlider::valueChanged,this,&Widget::soundValueChange);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    //获取全局坐标
    if(event->button()==Qt::LeftButton)
    {
        tempPos=event->pos();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    move(event->globalPos()-tempPos);
}

void Widget::setSheet()
{
    //隐藏边框
    setWindowFlag(Qt::FramelessWindowHint);
    //自动填充背景
    setAutoFillBackground(true);
    setPalette(QPalette(QColor(255,255,255,220)));
    //添加button图片
    ui->closeBtn->setStyleSheet("QPushButton{border-image:url(:/icon/关闭.png)}");
    ui->listBtn->setStyleSheet("QPushButton{border-image:url(:/icon/列表.png)}");
    ui->previousBtn->setStyleSheet("QPushButton{border-image:url(:/icon/上一首 (1).png)}");
    ui->nextBtn->setStyleSheet("QPushButton{border-image:url(:/icon/下一首 (1).png)}");
    ui->playBtn->setStyleSheet("QPushButton{border-image:url(:/icon/播放 (2).png)}");
    ui->soundBtn->setStyleSheet("QPushButton{border-image:url(:/icon/音量.png)}");
    ui->lovelyBtn->setStyleSheet("QPushButton{border-image:url(:/icon/爱心 (1).png)}");
    ui->labelBtn->setStyleSheet("QPushButton{border-image:url(:/icon/音乐.png)}");
    ui->sortBtn->setStyleSheet("QPushButton{border-image:url(:/icon/顺序循环.png)}");

    //列表设置
    list.setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    list.setAutoFillBackground(true);
    list.setPalette(QPalette(QColor(255,255,255,50)));
    list.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    slider.resize(120,12);
    slider.setAutoFillBackground(true);


    slider.setPalette(QPalette(QColor(255,255,255,100)));
    slider.setStyleSheet("  \
                        \
         QSlider::add-page:Horizontal\
         {     \
            background-color: rgb(87, 97, 106);\
            height:4px;\
         }\
         QSlider::sub-page:Horizontal \
        {\
            background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\
            height:4px;\
         }\
        QSlider::groove:Horizontal \
        {\
            background:transparent;\
            height:6px;\
        }\
        QSlider::handle:Horizontal \
        {\
            height: 30px;\
            width:8px;\
            border-image: url(:/images/ic_music_thumb.png);\
            margin: -8 0px; \
        }\
        ");

}


void Widget::on_listBtn_clicked()
{

    //
    if(isClicked)
    {
        isClicked=false;
        QPoint pos(QPoint(this->pos().x(),this->pos().y()+60));
        list.move(pos);
        list.resize(width(),height()*6);
        list.show();
    }else
    {
        isClicked=true;
        list.hide();

    }

}

void Widget::on_playBtn_clicked()
{
    if(isPlay)
    {
        //改变按钮图标
        ui->playBtn->setStyleSheet("QPushButton{border-image:url(:/icon/播放 (1).png)}");
//        QMediaContent content=player->currentMedia();
//        QUrl url=content.canonicalUrl();
//        qDebug()<<url.fileName();
        player->play();
        slider.setValue(player->volume());
        isPlay=false;
    }else
    {
        //改变按钮图标
        ui->playBtn->setStyleSheet("QPushButton{border-image:url(:/icon/播放 (2).png)}");
        player->pause();
        isPlay=true;
    }

}


void Widget::on_sortBtn_clicked()
{
    //设置静态变量 取余获取 0 ，1 ，2 三种状态
    static int i=0;
    if(i%3==1)
    {
        ++i;
        //顺序播放
        playList->setPlaybackMode(QMediaPlaylist::Loop);
        ui->sortBtn->setStyleSheet("QPushButton{border-image:url(:/icon/顺序循环.png)}");
    }else if(i%3==2)
    {
        ++i;
        //单曲循环
        playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        ui->sortBtn->setStyleSheet("QPushButton{border-image:url(:/icon/单曲循环.png)}");
    }else
    {
        ++i;
        //随机播放
        playList->setPlaybackMode(QMediaPlaylist::Random);

        ui->sortBtn->setStyleSheet("QPushButton{border-image:url(:/icon/随机播放.png)}");
    }


}

void Widget::on_previousBtn_clicked()
{
    playList->previous();
    qDebug()<<playList->currentIndex();
}

void Widget::on_nextBtn_clicked()
{
    qDebug()<<playList->currentMedia().canonicalUrl();
    playList->next();

    qDebug()<<playList->currentIndex();
}

void Widget::k(int row)
{
    qDebug()<<row;
    playList->setCurrentIndex(row);
}
//获取媒体文件中包含的数据
void Widget::metaDataAvailableChanged(bool available)
{
    if(available)
    {

    }
}

void Widget::moveEvent(QMoveEvent *event)
{
    QPoint posList(QPoint(event->pos().x(),event->pos().y()+60));
//    qDebug()<<event->pos();
    QPoint posSound(QPoint(event->pos().x()+230,event->pos().y()-12));
    slider.move(posSound);
    list.move(posList);
    list.resize(width(),height()*6);
}

void Widget::setSliderSt()
{

}

void Widget::on_soundBtn_clicked()
{
    if(isSoundedbtn)
    {
        QPoint posSound(QPoint(this->pos().x()+230,this->pos().y()-12));
        slider.move(posSound);
        slider.show();
        isSoundedbtn=false;
    }else
    {
        slider.hide();
        isSoundedbtn=true;
    }



}

void Widget::soundValueChange(int value)
{
    player->setVolume(value);

}
