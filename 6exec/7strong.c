#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void func(int sig)
{
	switch(sig)
	{
		case	SIGINT:
				puts("I don't care about Ctrl+c");
				break;
		case	SIGTERM:
				puts("kill me?no way");
				break;
		case	SIGTSTP:
				puts("I wil not stop");
				break;
	}
}

int main()//kill -KILL只剩必杀能用
{
	signal(SIGINT,func);//ctrl+c
	signal(SIGTERM,func);//kill -9/-TERM
	signal(SIGTSTP,func);//ctrl+z
	printf("pid=%d\n",getpid());
	for(;;)
	{
		write(STDERR_FILENO,".",1);
		sleep(1);//信号可能打断正在阻塞中的函数，使函数失败返回,这里失败返回剩余的秒数
	}
}
