#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
//select实现多路io(通过超时时间去检测那个可读)，也可以用于套接字，每个套接字都是一个文件描述符
int main()
{
	mkfifo("pipe1",0644);
	mkfifo("pipe2",0644);
	int fd1 = open("pipe1",O_RDWR);
	int fd2 = open("pipe2",O_RDWR);
	fd_set fs;//文件描述符集合
	struct timeval timeout={0,0};//超时时间为0，即不等待检测
	for(;;)
	{
	  FD_ZERO(&fs);
	  FD_SET(fd1,&fs);
	  FD_SET(fd2,&fs);
	  FD_SET(STDIN_FILENO,&fs);
	  char buf[1000];
	  if(select(fd2+1,&fs,NULL,NULL,&timeout)>0)//返回可读的文件描述符个数,如果没有可读就会一直跑大循环
	  {//处理三个文件描述符对应的文件中如果有数据可读就显示
		if(FD_ISSET(0,&fs))
		{//0表示标准输入文件stdin
		  scanf(" %[^\n]",buf);
		  if(strcmp(buf,"q")==0) break;
		  puts(buf);
		}
		if(FD_ISSET(fd1,&fs))
		{
		  int n = read(fd1,buf,sizeof(buf)-1);
		  buf[n] = '\0';
		  printf("pipe1:%s",buf);
		}
		if(FD_ISSET(fd2,&fs))
		{
		  int n = read(fd2,buf,sizeof(buf)-1);
		  buf[n] = '\0';
		  printf("pipe2:%s",buf);
		}
	  }
	}
	close(fd1);
	close(fd2);
	unlink("pipe1");
	unlink("pipe2");
}
