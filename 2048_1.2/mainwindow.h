#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QUrl>
#include <QtNetwork>
class QFile;

class QNetworkReply;
class QNetworkAccessManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startRequest(QUrl url);
private:
    QTextBrowser *browser;
    QGridLayout *mainLay;
    QNetworkAccessManager *manager;
    void replyFinished(QNetworkReply *);

    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64 max,qint64 val);

    void clicked_btn();

    QProgressBar *bar;
    QPushButton *btn;
    QLabel *la;
    QLineEdit *edit;

    QNetworkReply *reply;
    QUrl url;
    QFile *file;

};

#endif // MAINWINDOW_H
