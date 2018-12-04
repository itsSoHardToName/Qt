#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QHostAddress>
#define cout qDebug()<<__LINE__

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    setWindowTitle("服务端");
    port=8888;
    ui->sendBtn->setEnabled(false);
    ui->connectLine->setText(QString::number(port));
    servLis=new QTcpServer(this);
    servLis->listen(QHostAddress::Any,port);

    connect(servLis,&QTcpServer::newConnection,[=](){
        QString str="xiaolizi:hello i'm lizi!";
        servSok=servLis->nextPendingConnection();
        ui->sendBtn->setEnabled(true);
        servSok->write(str.toLatin1(),str.length());
        connect(servSok,&QTcpSocket::readyRead,this,&Widget::readData);
    });
    connect(ui->sendBtn,&QPushButton::clicked,this,&Widget::sendData);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendData()
{
    QString str=ui->sendLine->text();
    int length=str.length();
    if(length>0)
    servSok->write("lizi:"+str.toLatin1(),length+sizeof("lizi:"));
    ui->sendLine->clear();
}
void Widget::readData()
{
    QByteArray array;
    array=servSok->readAll();
    ui->listWidget->addItem(array);
}

