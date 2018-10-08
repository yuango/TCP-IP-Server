#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
//udp协议，在同一个局域网里，只用先设置本机port，然后直到对方ip和port即可发送消息，而接收消息是只要有人能发进来就能收到并保存对方套接信息，可以用于回复对方(实际上：发送来的数据会被暂存起来，当调用接收函数时会从缓存中读取该数据，而且每次只接收一个发来的数据，且按先后发来的顺序)

typedef struct sockaddr *sa;
struct sockaddr_in ss;
char ip1[16];
void *func(void *p)
{
	int skt1 = *(int *)p;
	char text1[1000];
	socklen_t len = sizeof(ss);//存放对方套接信息的长度，需要先初始化成结构体长度
	for(;;)
	{
	  int n = recvfrom(skt1,text1,sizeof(text1),0,(sa)&ss,&len);//这里len取地址是因为需要填充这个值(修改)，所以需要传地址给函数.(如果没有信息过来，就一直等待（标志为0），失败返回-1)
	  if(n<0)
	  {
	    perror("接收消息失败");
//	usleep(10000);//不实时(但是由于缓存接收到的数据所以不会丢失很多数据)，但是降低循环次数，降cpu
	    continue;//继续下次循环
	  }
	  inet_ntop(AF_INET,&ss.sin_addr,ip1,sizeof(ip1));
	  printf("%s %hd:%s\n",ip1,ntohs(ss.sin_port),text1);//text中字符串是有结束标志的,输出时候要把端口号的网络格式转到本机格式
	}
}

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
	  printf("格式：%s PORT\n",argv[0]);
	  return 0;
	}
//创建套接字
	int skt = socket(AF_INET,SOCK_DGRAM,0);
//服务器套接信息存在结构体中
	struct sockaddr_in s;
	s.sin_family = AF_INET;
	s.sin_addr.s_addr = INADDR_ANY;//主机
	s.sin_port = htons(atoi(argv[1]));
//绑定成为udp服务器
	if(bind(skt,(sa)&s,sizeof(s))<0)
	{
	  perror("bind falied");
	  return -1;
	}
/*
数据传输格式：
s/r ip port text
a text 回复
q 退出
*/
	char cmd;
	char ip[16];
	short port;//2字节
	char text[1000];//文本暂存
	pthread_t id;
	pthread_create(&id,NULL,func,&skt);
	for(;;)
	{
	  printf("s/a/q:");
	  scanf(" %c",&cmd);
	  if(cmd == 'q')
	  {
		puts("Exit");
		break;
	  }
//发送数据的时候需要指定对方的套接信息存到结构体中
	  if(cmd == 's')
	  {
		printf("Send to IP:");
		scanf("%s",ip);
		printf("Port:");
		scanf("%hd",&port);
		puts("Message:");
		scanf(" %[^\n]",text);//%hd(short int),text文本跳过空格等直到遇到换行符为止
		s.sin_family = AF_INET;
		inet_pton(AF_INET,ip,&s.sin_addr);
		s.sin_port = htons(port);//这里的port在输入时就是以短整型存储的，而命令行argv[]中是存储的字符串地址
		sendto(skt,text,strlen(text)+1,0,(sa)&s,sizeof(s));//strlen以'\0'为止,+1把'\0'也发出去
	  }
/*****用辅助线程循环跑接收消息***********
	  else if(cmd == 'r')
	  {
		socklen_t len = sizeof(s);//存放对方套接信息的长度，需要先初始化成结构体长度
		int n = recvfrom(skt,text,sizeof(text),MSG_DONTWAIT,(sa)&s,&len);//这里len取地址是因为需要填充这个值(修改)，所以需要传地址给函数
		if(n<0)
		{
		  puts("没有收到消息");
		  continue;//继续下次循环
		}
		inet_ntop(AF_INET,&s.sin_addr,ip,sizeof(ip));
		printf("%s %hd:%s\n",ip,ntohs(s.sin_port),text);//text中字符串是有结束标志的,输出时候要把端口号的网络格式转到本机格式
	  }
******************************************/
	  else if(cmd == 'a')
	  {//回复收到的信息，即前一个循环必须是接收，接收函数会把发送者的套接信息保存到结构体s中(所以如果运行发送函数会改变这个结构体s中的成员变量值)
//		strcpy(ip,ip1);
		s.sin_family = ss.sin_family;
		s.sin_addr = ss.sin_addr;
		s.sin_port = ss.sin_port;//防止在回复的过程中接收到信息，改变原来想回复的对方套接信息
		inet_ntop(AF_INET,&s.sin_addr,ip,sizeof(ip));//这里防止一上来就回复的情况，这样就显示回复本机ip
		printf("Reply to:%s %hd\nInput Message:\n",ip,ntohs(s.sin_port));
		scanf(" %[^\n]",text);
		sendto(skt,text,strlen(text)+1,0,(sa)&s,sizeof(s));//+1表示把字符串结束符'\0'也发送
	  }
	  else
	  {
		puts("非法命令！");
		fflush(stdin);//清除输入缓冲区。有的系统不可用
	  }
	}
	close(skt);
}
