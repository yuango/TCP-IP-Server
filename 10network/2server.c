#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
//单线程简单通信
int main()
{
//话机socket
	int fd = socket(AF_INET,SOCK_STREAM,0);//创建套接字,ipv4,tcp
	if(fd<0)
	{
	  perror("socket failed");
	  return -1;
	}
//绑定bind,区分不同应用程序-->先设套接信息，端口port(和ip合称套接信息)
	struct sockaddr_in si;//套接信息必须存到结构体中
	si.sin_family = AF_INET;//ipv4
	si.sin_addr.s_addr = htonl(INADDR_ANY);//0为本机ip地址，实际0也可以不转格式
	si.sin_port = htons(8888);//1024以下的端口被内定为专门用途，所以选端口号至少1024.需要转格式成网络格式(2字节)
//bind(int fd,sockaddr *,size_t);失败返回-1
	if(bind(fd,(struct sockaddr *)&si,sizeof(si))<0)
	{
	  perror("bind failed");
	  return -1;
	}
//允许多路接入，listen
	listen(fd,10);//允许同时有10个接入请求，已经连接的不算
//反复等待客户连接
	for(;;)
	{
	  struct sockaddr_in c;//客户端套接信息也必须用结构体
	  socklen_t len = sizeof(c);//必须初始化成本地的套接信息长度
	  /*
	  **return 非负整数(成功)，-1(失败)
	  **阻塞等待
	  */
	  int fc = accept(fd,(struct sockaddr *)&c,&len);//等待客户连接，服务器fd取得接入的对方(客户端)的socket信息存入结构体c中,返回一个跟该客户相连的新的(是服务器的分支)套接字(分机)
	  if(fc<0)
	  {//连接客户出错，无所谓
		continue;//跳过本次循环，继续下次循环
	  }
	//成功先打印出连接进来的客户端信息
	  char cip[16];//client客户端
	  inet_ntop(AF_INET,&c.sin_addr,cip,sizeof(cip));//内部格式转成点分十进制格式的字符串
	  printf("ip:%s到此一游\n",cip);
	  char msg[1000];
	  sprintf(msg,"Your IP:%s,welcom to network\n",cip);
//反复通信，这里只是主机向分机(与客户端直接通信)动作的程序
	  write(fc,msg,strlen(msg));//给分机发也就相当于和客户端通信
	  close(fc);//挂断分机,断开与客户端连接
	}
}
