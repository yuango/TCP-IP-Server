#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void func(int sig)//这是自定义信号处理函数标准形式
{
	int fd = open("data",O_RDONLY);
	if(fd<0)
	{
		perror("open failed");
		return;
	}
	char buf[100];
	int len = read(fd,buf,sizeof(buf));
	if(len>0)
	{
		buf[len] = '\0';
		puts(buf);
	}
	close(fd);
	unlink("data");
	if(!strcmp(buf,"q")) raise(SIGTERM);
}

int main()
{
	signal(SIGUSR1,func);
	printf("pid=%d\n",getpid());
	for(;;)
	{
	  sleep(100);//等信号到的时候转去处理信号
	}
}
