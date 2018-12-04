#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void sendData();
    void readData();


private:
    Ui::Widget *ui;
    int port;
    QTcpServer *servLis;
    QTcpSocket *servSok;
};

#endif // WIDGET_H
