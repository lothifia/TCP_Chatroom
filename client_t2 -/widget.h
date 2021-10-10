#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include<QtNetwork>
#include<QMessageBox>
#include<string>
#include<pthread.h>
#include<QThread>
#include "mythread.h"

#define MCPORT 9999
#define MCIP  "239.0.0.2"
#define UPORT 7777
#define SPORT 8000
#define SIP "bu'gao'suni "

#pragma comment(lib,"ws2_32.lib")

#define MAXN 1024

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QMessageBox mgb;

    int wsa_error;
    SOCKET sockfd;
    struct sockaddr_in servaddr;
    std::string buf;
    WSADATA wsad;//in windows must WSAD!
    char l_buf[MAXN];

    Mythread* t1;

    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void on_send_clicked();

    void on_connect_clicked();

    void on_disconnect_clicked();

    void hand_sig(QString);

private:
    Ui::Widget *ui;
    int _cnt;
};
#endif // WIDGET_H
