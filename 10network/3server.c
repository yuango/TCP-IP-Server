#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>//用到多线程，编译时加-pthread
#include <stdlib.h>
//多线程：主机等待别的客户端，分机跟客户通信

struct Param{
	int fc;
	char ip[16];
};

void *func(void *p)
{//辅助线程，分机工作与客户端通信
	struct Param *r = p;//转类型
	for(;;)
	{//read/write不关心数组中是否是字符串，他们只关心数据
	  char msg[1000];
	  int n = read(r->fc,msg,sizeof(msg)-1);//读来自客户端的信息(注意换行和回车符也算在其中),-1防止数组加'\0'时越界(一般不会发生).（或许如果没有信息会一直等待在这里直到客户端发信息过来，读取完也会清空该虚拟文件？？）
printf("接收客户端%d个字符\n",n);//测试n
	  if(msg[0]=='q' && n==2) break;//有的n=3-->'q'+'\r'+'\n',跳转close()
	  if(n<=0) 
	  {
		puts("读取客户端失败");
		break;//检查是否出错或者关闭
	  }
	  write(r->fc,msg,n);//将客户端发来的数据回发到客户端。(有的客户端这时便会显示出该数据)
//	  msg[n] = '\0';//手动加上字符串结束标记
msg[n-1] = '\0';//去'\n'(有的需要去掉发送过来的换行和回车符)
	  printf("%s:%s\n",r->ip,msg);//主机显示客户端发送来的字符串
	}
	close(r->fc);//关闭套接字，关闭分机(与客户端断开连接)
	printf("IP：%s 退出连接\n",r->ip);
	free(p);//释放动态内存
}

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
	{//将服务器套接字和主机ip以及端口号绑定
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
	  int fc = accept(fd,(struct sockaddr *)&c,&len);//等待客户连接，服务器fd取得接入的对方(客户端)的socket信息存入结构体c中,返回一个跟该客户相连的新的套接字。如果没有客户端接入，主机(主线程)就一直等待在这里，不会结束
	  if(fc<0)
	  {//连接客户出错，无所谓
		continue;//跳过本次循环，继续下次循环(下面跳过执行)
	  }
	//成功先打印出连接进来的客户端信息
	  char cip[16];//client客户端
	  inet_ntop(AF_INET,&c.sin_addr,cip,sizeof(cip));//内部格式转成点分十进制格式的字符串
	  printf("IP：%s 连接成功\n",cip);//程序中的显示函数都是在服务器(主机和分机)端显示的
	  char msg[1000];
	  sprintf(msg,"Your IP:%s,welcom to network\n",cip);//给客户端的信息存到数组中
//通信
	  write(fc,msg,strlen(msg));//给客户端发送字符串,而客户端怎么处理(显示还是怎样)由其自身处理函数决定
//	  close(fc);//挂断分机
//多线程分工
	  pthread_t id;//辅助线程
	  struct Param *p = malloc(sizeof(struct Param));//用于保存辅助线程func要传的多个参数
	  p->fc = fc;//由通过连接客户端而产生的套接字(相当于客户端文件)
	  strcpy(p->ip,cip);//客户端ip
	  pthread_create(&id,NULL,func,p);//辅助线程即分机与客户端的反复通信工作，需要传递客户端的几个参数
	}
}
