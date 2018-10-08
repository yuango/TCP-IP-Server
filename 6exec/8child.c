#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void func(int sig)
{
	int info;//存储状态信息
	pid_t cid;
//	cid = waitpid(-1,&info,WNOHANG);//任意子进程不等待，但是如果有积压的多个相同的信号，可能在处理时合并为一个来处理.收到一个信号可能有好几个子进程结束了
	while((cid = waitpid(-1,&info,WNOHANG))>0)//不积压处理
	printf("%d结束，返回%d\n",cid,WEXITSTATUS(info));//返回值为子进程退出时的返回值exit(c)
}

int main()
{
	int i;
	system("clear");//运行前清屏
	signal(SIGCHLD,func);//子进程结束或中断时，给父进程发送信号SIGCHLD
	for(i=0;i<10;i++)//产生10个子进程
	{
		if(fork()==0)
		{
			int j;
			char c = 'A'+i;
			for(j=0;j<20;j++)
			{
				write(1,&c,1);//注意&c的用法
				sleep(1);
			}
			exit(c);//子进程跑20秒在此结束
		}//父进程继续循环产生子进程
	}
	for(;;)//父进程运行在这里，等待子进程结束
	{
		sleep(100);
	}
}
