#include "widget.h"
#include "ui_widget.h"

//void* Widget::Trecv(void*){
//    char lb[MAXN];
//    while(1){
//        memset(lb, 0, sizeof (lb));
//        if(recv(sockfd, lb, sizeof (lb), 0)){
//            QString str = QString::fromLocal8Bit(lb, sizeof (lb));
//            this->ui->recv_t->setText(ui->recv_t->toPlainText() + "\n" + str);
//        }
//    }
//}
void Widget::hand_sig(QString s){
    QString pre = ui->recv_t->toPlainText();
    pre += "\n" + s + "\n";
    ui->recv_t->setText(pre);
}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    wsa_error =  WSAStartup(MAKEWORD(2,2),&wsad);
    _cnt = 0;
    ui->setupUi(this);
}

Widget::~Widget()
{
    WSACleanup();
    delete ui;

}


void Widget::on_send_clicked()
{

    buf = ui->send_t->toPlainText().toStdString();
     if(send(sockfd,buf.c_str(),buf.size(), 0) <= 0){
         mgb.setText("false\n");
         mgb.exec();
         closesocket(sockfd);
         return ;
     }

}

void Widget::on_connect_clicked()
{
    if(_cnt != 0){
         mgb.setText("禁止多次链接!");
         mgb.exec();
         return;
    }
    _cnt++;
    if(wsa_error != NO_ERROR){
        return;
    }
    if ((sockfd=socket(AF_INET,SOCK_STREAM,0))<0) { mgb.setText("socket() failed.\n");
        mgb.exec();
        return ;}


    mgb.setText("now connecting....\n");
    mgb.exec();
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SPORT);
    servaddr.sin_addr.s_addr=inet_addr(SIP);
    if (::connect(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)) != 0)
    {
        char tem[1024];
        sprintf(tem,"connect(%s) failed.\n",SIP);
        mgb.setText(tem);
        mgb.exec();

        closesocket(sockfd);
        return;
    }
    t1 = new Mythread(sockfd);
    connect(t1, SIGNAL(Send2UI(QString)), this, SLOT(hand_sig(QString)));
    t1->start();

    mgb.setText("connect ok.\n");
    mgb.exec();

}

void Widget::on_disconnect_clicked()
{
    if(_cnt == 0){
        mgb.setText("还没链接!");
        mgb.exec();
        return;
    }
    _cnt--;
    //thread quit
    t1->terminate();
    closesocket(sockfd);
}
