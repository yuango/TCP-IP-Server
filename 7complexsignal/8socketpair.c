#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int s[2];//套结字对，也是文件描述符
	socketpair(AF_LOCAL,SOCK_STREAM,0,s);
	int n;
	char buf[100];
	if(fork()==0)
	{//子进程
printf("子进程：%d\n",getpid());
		while((n=read(s[0],buf,sizeof(buf)))>0)//如果子进程不手动结束，这里会一直阻塞在read函数
		{//确实读出内容
if(n==2 && buf[0]=='q') break;//这里如果不手动结束子进程，则最后子进程会变成孤儿进程(即不会自动结束)
		  int i;
		  n--;//0-n-1共n个字符，保留末尾换行符
		  for(i=0;i<n/2;i++)
		  {
			char c = buf[i];
			buf[i]=buf[n-1-i];
			buf[n-1-i] = c;
		  }
		  write(s[0],buf,n+1);
		}
		close(s[0]);//套结字对是否需要手动关闭??
puts("子over");
	}
	else
	{
printf("父进程：%d\n",getpid());
		for(;;)
		{
		  n = read(STDIN_FILENO,buf,sizeof(buf));
		  write(s[1],buf,n);//buf中是没有'\0'的.这边写了，子进程才能读
		  if(n==2 && buf[0]=='q') break;//换行符也算在内
		  n = read(s[1],buf,sizeof(buf));//子进程写了这边才能读
		  write(STDOUT_FILENO,buf,n);
		}
		close(s[1]);
usleep(100000);
puts("父over");
	}
}
