#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainLay=new QGridLayout(this);
    browser=new QTextBrowser(this);
    btn=new QPushButton(this);
    la=new QLabel(tr("URL"),this);
    bar=new QProgressBar(this);
    edit=new QLineEdit(this);
    bar->hide();
    mainLay->addWidget(browser,0,0,1,1);
    mainLay->addWidget(la,1,0);
    mainLay->addWidget(edit,1,1);
    mainLay->addWidget(bar,2,0);
    mainLay->addWidget(btn,2,1);
    QWidget *w=new QWidget(this);
    w->setLayout(mainLay);

    setCentralWidget(w);DSD
    manager=new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,
            &MainWindow::replyFinished);
    manager->get(QNetworkRequest(QUrl("http://www.baidu.com")));
    connect(btn,&QPushButton::clicked,this,&MainWindow::clicked_btn);
}

MainWindow::~MainWindow()
{

}

void MainWindow::startRequest(QUrl url)
{
    reply= manager->get(QNetworkRequest(url));
    connect(reply,&QNetworkReply::readyRead,this,&MainWindow::httpReadyRead);
    connect(reply,&QNetworkReply::downloadProgress,this,
            &MainWindow::updateDataReadProgress);
    connect(reply,&QNetworkReply::finished,this,
            &MainWindow::httpFinished);

}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    QString all=reply->readAll();
    browser->setText(all);
    reply->deleteLater();
}

void MainWindow::httpFinished()
{
    bar->hide();
    file->flush();
    file->close();
    reply->deleteLater();
    reply=0;
    delete file;
    file=0;
}

void MainWindow::httpReadyRead()
{
    if(file)file->write(reply->readAll());
}

void MainWindow::updateDataReadProgress(qint64 max, qint64 val)
{
    bar->setMaximum(max);
    bar->setValue(val);
}

void MainWindow::clicked_btn()
{
    url=edit->text();
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    file=new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly))
    {
        qDebug()<<"file open error";
        delete file;
        file=0;
        return ;
    }
    startRequest(url);
    bar->setValue(0);
    bar->show();
}
