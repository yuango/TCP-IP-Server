#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>//fd
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	if(argc!=3)
	{//命令格式不正确就给出提示
	  printf("%s serverip port\n",argv[0]);
	  return 0;
	}
//产生套接字
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd<0)
	{
	  perror("socket failed");
	  return -1;
	}
//结构体保存服务器套接信息
	struct sockaddr_in c;
	c.sin_family = AF_INET;
	inet_pton(AF_INET,argv[1],&c.sin_addr);//严格应该检查是否成功。内部格式ip地址是存在结构体in_addr中的(sin_addr的类型就是结构体in_addr),而如果想取得具体值用c.sin_addr.s_addr(取到结构体in_addr的唯一成员s_addr)
	c.sin_port = htons(atoi(argv[2]));//先用atoi将命令行输入的字符8888转成int型，然后用htons将主机格式转成网络字节顺序(总结：网络通信的程序设计中都要把字节顺序转成网络字节顺序)
//连接服务器
	if(connect(fd,(struct sockaddr *)&c,sizeof(c))<0)
	{//连接之后的fd表示的文件就成为服务器与客户端之间的共享文件，实现相互通信
	  perror("connect failed");
	  return -1;
	}
	puts("连接成功");
//反复通信
	char msg[1000];
	for(;;)
	{
	  int n = read(fd,msg,sizeof(msg));//读取来自服务器数据(如果服务器没有发送来信息，这里会一直等待吗？？经过测试，程序确实停在这里没有执行到Input.读完也会清空该虚拟文件吗??)
	  if(n<=0) break;
	  write(STDOUT_FILENO,msg,n);//显示到客户端屏幕
	  printf("Input:");
	  scanf(" %[^\n]",msg);//读到换行符为止
	  strcat(msg,"\n");//追加换行符。也可以代替以上两行用fgets(msg,sizeof(msg),stdin);从标准输入端写入字符串存入数组，包括换行符
	  write(fd,msg,strlen(msg));//发送到服务器
	  if(msg[0]=='q') break;//退出
	}
	close(fd);//关闭套接字
}
