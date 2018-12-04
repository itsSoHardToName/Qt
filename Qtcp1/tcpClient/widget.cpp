#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QDebug>
#define cout qDebug()<<__LINE__
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    clientSoc= new QTcpSocket(this);
    setWindowTitle("客户端");
    ui->sendBtn->setEnabled(false);
    connect(ui->connectBtn,&QPushButton::clicked,[=](){
        ip=ui->ipLine->text();
        port=ui->portLine->text().toUInt();
        clientSoc->connectToHost(QHostAddress(ip),port);

        QString str="DALIZI : hello i'm LIZI !";
        clientSoc->write(str.toLatin1(),str.length());
        connect(clientSoc,&QTcpSocket::readyRead,this,&Widget::readData);
    });
    connect(ui->sendBtn,&QPushButton::clicked,this,&Widget::sendData);
    connect(clientSoc,&QTcpSocket::connected,this,&Widget::succeed);

}
Widget::~Widget()
{
    delete ui;
}

void Widget::readData()
{
    QByteArray array;

    array=clientSoc->readAll();
    ui->listWidget->addItem(array);
}

void Widget::sendData()
{
    QString str=ui->sendLine->text();
    if(str.length()>0)
        clientSoc->write("LIZI:"+str.toLatin1(),str.length()+sizeof("LIZI:"));
    ui->sendLine->clear();
}

void Widget::succeed()
{
    ui->sendBtn->setEnabled(true);
}
