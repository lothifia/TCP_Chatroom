#include"mythread.h"
#include <QMutex>
#include<winsock2.h>


Mythread::Mythread(int fd){
    sockfd = fd;
}

void Mythread::run(){
    char buff[1024];
    while(!isInterruptionRequested()){
        memset(buff, 0, sizeof (buff));
        if(recv(sockfd, buff, sizeof (buff),0)){
            QString str = QString::fromUtf8(buff, strlen(buff));
            emit(Send2UI(str));
        }
    }
}
Mythread::~Mythread()
{

}
