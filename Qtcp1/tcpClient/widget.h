#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
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
    void readData();
    void sendData();
    void succeed();
private:
    Ui::Widget *ui;
    QTcpSocket *clientSoc;
    int port;
    QString ip;
};

#endif // WIDGET_H
