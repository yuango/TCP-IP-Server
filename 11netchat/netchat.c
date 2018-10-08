#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>//for isxxx(char)
//聊天室，广播所有进入客户端发送的消息
//无论服务器还是客户端关闭对应的套接字，那么另一方就会因为read/write函数无法正常执行而退出
#define MAX 100//接入的客户数量
typedef struct sockaddr *sa;
typedef struct {
	int s;//socket，客户端接入成功产生的套接字
	char ip[16];//有内部格式转成的点分十进制格式ip地址字符串
} client;

client cs[MAX];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void broadcast(int c,void *msg,int n)
{
	write(1,msg,n);//stdout,在服务器终端上显示该信息
	pthread_mutex_lock(&m);
	int i;
	for(i=0;i<MAX;i++)
	{
	  if(cs[i].s!=0&&cs[i].s!=c)//除了发送的客户端给所有接入的客户端广播(cs[i].s的值是不可能为1或2的,且为0是初始值)
		write(cs[i].s,msg,n);
	}
	pthread_mutex_unlock(&m);
}

void *func(void *p)
{//传参p = &cs[i](原来类型是client *,所以需要还原类型)
	client *q = p;
	char ip[16];
	pthread_mutex_lock(&m);
	int c = q->s;//这里还是通过地址访问了结构体cs[],所以需要加锁
	strcpy(ip,q->ip);//先将结构体成员取出来，减少互斥锁时间，提高实时性
	pthread_mutex_unlock(&m);
	char msg[1000];
	int n = sprintf(msg,"欢迎%s进入聊天室\n",ip);//返回字符数量
	broadcast(0,msg,n);//给所有进入的客户端广播新进来的客户端
	int iplen = sprintf(msg,"%s说：",ip);
	char *info = msg+iplen;//info指向数组中存的“：”后面
	for(;;)
	{
	  int len = read(c,info,sizeof(msg)-iplen);//将读到的数据保存在数组偏移iplen的位置以后，长度最大是数组长度减去已经占用的iplen长度(这里如果客户端没有发来消息则会一直等待)
	  if(len<=0) break;//如果客户端关闭(不是正常q退出),read返回0
	  if(info[0]=='q'&&isspace(info[1]))
	  {//判断是否空格等无用字符(包括换行符等)
		break;
	  }
	  broadcast(c,msg,len+iplen);
	}
	pthread_mutex_lock(&m);
	q->s = 0;//这时套接字作废，将套结字设为0，使得主线程中判断结构体中成员s是否为0(空位置)正常进行
	pthread_mutex_unlock(&m);
	close(c);//关闭无用套接字
	n = sprintf(msg,"%s退出聊天室\n",ip);
	broadcast(0,msg,n);
}

void *quit(void *p)
{
  for(;;)
  {
	char buff[100];
	scanf(" %[^\n]",buff);
	if(!strcmp(buff,"exit"))
	{
	  printf("%s关闭服务器\n",(char *)p);
	  exit(0);
	}
  }
}

int main()
{
	pthread_t id0;
	pthread_create(&id0,NULL,quit,"*");
	int s = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_addr.s_addr = INADDR_ANY;//只能给结构成员变量直接赋值
	si.sin_port = htons(8888);
	if(bind(s,(sa)&si,sizeof(si))<0)
	{
	  perror("bind failed");
	  return -1;
	}
	listen(s,5);
	for(;;)
	{
	  socklen_t len = sizeof(si);
	  int c = accept(s,(sa)&si,&len);//没必要再定义一个结构(用来存储连接进来的客户端IP+PORT信息),排队每次只能接受一个client,会block
	  if(c<0) continue;
	  int i;
	  pthread_mutex_lock(&m);//互斥锁，用来锁住结构体数组cs[]
	  for(i=0;i<MAX&&cs[i].s!=0;i++)
	  {
		//循环找出第一个cs[i].s==0的
	  }
	  if(i==MAX)
	  {//没有空位置
		write(c,"refused:full\n",13);//给该连入的客户端发
		close(c);
	  }
	  else
	  {//接入客户端限制没满
		cs[i].s = c;
		inet_ntop(AF_INET,&si.sin_addr,cs[i].ip,16);//此时结构体si中存的是新接入的套接信息
		pthread_t id;
		pthread_create(&id,NULL,func,&cs[i]);
	  }
	  pthread_mutex_unlock(&m);
	}
}
