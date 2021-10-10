#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
class Mythread : public QThread{
    Q_OBJECT
public:
    Mythread(int fd);
    ~Mythread();
    void run() override;
signals:
    void Send2UI(QString str);
private:
    int sockfd;
    volatile bool stop;
};

#endif // MYTHREAD_H
