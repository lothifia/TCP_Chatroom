#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include<net/if.h>
#include <pthread.h>


#define MCPORT 9999
#define MCIP  "239.0.0.2"
#define UPORT 7777
#define SPORT 8000
int sockfd;

void* th_recv(void* arg){

  char buffer[1024];

  while(1){
    memset(buffer, 0, sizeof(buffer));
    if(read(sockfd, buffer, sizeof(buffer)) < 0){
      printf("udp recv fail!");
    }
    else{
      printf("recv:%s\n", buffer);
    }

  }

}

int main(int argc,char *argv[])
{
  if (argc!=2)
  {
    printf("Using:./client ip port\nExample:./client 127.0.0.1 5005\n\n"); return -1;
  }


  // connect sockfd
  if ( (sockfd = socket(AF_INET,SOCK_STREAM,0))==-1) { perror("socket"); return -1; }
 
  struct hostent* h;
  if ( (h = gethostbyname(argv[1])) == 0 )   // ip
  { printf("gethostbyname failed.\n"); close(sockfd); return -1; }
  struct sockaddr_in servaddr;
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SPORT); // target port
  memcpy(&servaddr.sin_addr,h->h_addr,h->h_length);
  if (connect(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)) != 0)  // 向服务端发起连接清求。
  { perror("connect\n"); close(sockfd); return -1; }

  //recv pthread
  pthread_t thid;
  if(pthread_create(&thid, NULL, th_recv, NULL) != 0){
    perror("pthread fail!!\n");
    exit(1);
  }

  printf("pthread finish\n");
  
  char buffer[1024];
 
  while(1)
  {
    memset(buffer, 0, sizeof(buffer));
    printf("plear enter:\n ");
    scanf("%s", &buffer);
    // sprintf(buffer,"nihao\n");
    int err = 0;
    if(err = send(sockfd, buffer, strlen(buffer),0) <= 0){
      printf("%d",err);
      perror("send\n");
      break;
    }
  }
 
  close(sockfd);
}
