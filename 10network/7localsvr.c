#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/un.h>
#include <pthread.h>
//本地套结字利用套接字文件来连接通信
//服务器给所有连进来的客户端发同样的消息,使用本地套接字时协议用tcp或者udp无所谓，使用udp相当于管道
typedef struct sockaddr *sa;
int fds[8];//保存所有的客户端，没有初始化，但是初始值默认为0
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *input(void *p)
{
	for(;;)
	{
	  printf("Input:");
	  char text[1000];
	  scanf(" %[^\n]",text);
	  if(strcmp(text,"q")==0) break;
	  int i;
	  pthread_mutex_lock(&m);
	  for(i=0;i<8;i++)
	  {
		if(fds[i]!=0)
		{
		  write(fds[i],text,strlen(text));
		}
	  }
	  pthread_mutex_unlock(&m);
	}
	close(*(int *)p);
	unlink("yoyo");//必须删除，不然下次运行会报错地址已经被使用
	pthread_mutex_destroy(&m);
	exit(0);//结束进程,结束主线程的等待，也让客户端结束
}

int main()
{
	int fd = socket(AF_LOCAL,SOCK_STREAM,0);
	struct sockaddr_un s;
	s.sun_family = AF_LOCAL;
	strcpy(s.sun_path,"yoyo");
	if(bind(fd,(sa)&s,sizeof(s))<0)
	{
	  perror("bind failed");
	  return -1;
	}
	listen(fd,5);
	pthread_t id;
	pthread_create(&id,NULL,input,&fd);
	for(;;)
	{
	  socklen_t len = sizeof(s);
	  int c = accept(fd,(sa)&s,&len);
	  if(c<0) continue;
	  int i;
	  pthread_mutex_lock(&m);//加锁数组fds
	  for(i=0;i<8&&fds[i]!=0;i++){}//将每次连接的客户端套接字保存到空的fds数组中
	  if(i==8)
	  {//如果没有空数组则表示连接超过限制了，此时就关闭连接的客户端套接字
		puts("客户端连接超限");
		close(c);
	  }
	  else
		fds[i] = c;
	  pthread_mutex_unlock(&m);
	}
}
