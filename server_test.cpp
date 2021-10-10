#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unordered_set>
#include<unordered_map>
#include <net/if.h>
#include <utility>



#define MAXEVENTS 100
#define MCPORT 9999
#define MCIP  "239.0.0.2"
#define MAXN 1024
#define SPORT 8000
#define UPORT 7777


//record total user
std::unordered_set<int> sss;

int setnonblocking(int sockfd);

int initserver(int port);

int main(int argc,char *argv[])
{

  char buffer[MAXN];
  memset(buffer,0,sizeof(buffer));
  int listensock = initserver(SPORT);
  if (listensock < 0)
  {
    printf("initserver() failed.\n"); return -1;
  }

  int epollfd;
  epollfd = epoll_create(1);
  struct epoll_event ev;
  ev.data.fd = listensock;
  ev.events = EPOLLIN;
  epoll_ctl(epollfd,EPOLL_CTL_ADD,listensock,&ev);
//tcp over

  //epoll 
  while (1)
  {
    struct epoll_event events[MAXEVENTS]; // 存放有事件发生的结构数组。

    int infds = epoll_wait(epollfd,events,MAXEVENTS,-1);
     printf("epoll_wait infds=%d\n",infds);

    if (infds < 0)
    {
      printf("epoll_wait() failed.\n"); perror("epoll_wait()"); break;
    }

    // 超时。
    if (infds == 0)
    {
      printf("epoll_wait() timeout.\n"); continue;
    }

    for (int ii=0;ii<infds;ii++)
    {
      if ((events[ii].data.fd == listensock) &&(events[ii].events & EPOLLIN))
      {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int clientsock = accept(listensock,(struct sockaddr*)&client,&len);
        if (clientsock < 0)
        {
          printf("accept() failed.\n"); continue;//need notice client
        }

        


        // add new client to send target (recv )
           printf("new custome come\n");
           sss.insert(clientsock);
        memset(&ev,0,sizeof(struct epoll_event));
        ev.data.fd = clientsock;
        ev.events = EPOLLIN;
        epoll_ctl(epollfd,EPOLL_CTL_ADD,clientsock,&ev);

        printf ("client(socket=%d) connected ok.\n",clientsock);

        continue;
      }
      else if (events[ii].events & EPOLLIN)
      {
        char buffer[1024];
        memset(buffer,0,sizeof(buffer));

        ssize_t isize=read(events[ii].data.fd,buffer,sizeof(buffer));

        if (isize <=0)
        {
          printf("client(eventfd=%d) disconnected.\n",events[ii].data.fd);

          //close
          close(users[events[ii].data.fd]);
          //erase client from users
          sss.erase(events[ii].data.fd);
          memset(&ev,0,sizeof(struct epoll_event));
          ev.events = EPOLLIN;
          ev.data.fd = events[ii].data.fd;
          epoll_ctl(epollfd,EPOLL_CTL_DEL,events[ii].data.fd,&ev);
          close(events[ii].data.fd);
          continue;
        }

        printf("recv(eventfd=%d,size=%d):%s\n",events[ii].data.fd,isize,buffer);
        for(auto i = sss.begin(); i != sss.end();i++){
          printf("send to %d\n", *i);
            write(*i, buffer, sizeof(buffer));
        }
        //write(events[ii].data.fd,buffer,strlen(buffer));
      }
    }
  }

  close(epollfd);

  return 0;
}

int initserver(int port)
{
  int sock = socket(AF_INET,SOCK_STREAM,0);
  if (sock < 0)
  {
    printf("socket() failed.\n"); return -1;
  }

  int opt = 1; unsigned int len = sizeof(opt);
  setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,len);
  setsockopt(sock,SOL_SOCKET,SO_KEEPALIVE,&opt,len);

  struct sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if (bind(sock,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 )
  {
    printf("bind() failed.\n"); close(sock); return -1;
  }

  if (listen(sock,5) != 0 )
  {
    printf("listen() failed.\n"); close(sock); return -1;
  }

  return sock;
}

int setnonblocking(int sockfd)
{  
  if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1)  return -1;

  return 0;  
}  
