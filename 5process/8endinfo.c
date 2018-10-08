#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void childprocess()
{
	int i;
	printf("myid=%d\n",getpid());
	for(i=0;i<20;i++)
	{
		write(STDOUT_FILENO,"*",1);
		usleep(500000);
	}
	puts("it's over");
	exit(88);
}

int main()
{
	if(fork()==0)//子进程动作
	{
		childprocess();
	}
	else//父进程动作
	{
		puts("等待子进程结束");
		int info;
		pid_t id = wait(&info);//停在这等待子进程结束
		printf("子进程%d结束\n",id);//也可以加个判断
		if(WIFEXITED(info))//判断是否正常结束
		{
		  printf("正常结束，返回%d\n",WEXITSTATUS(info));//取得结束时的返回值(即子进程结束的返回值，88)
		}
		else
		{
		  printf("非正常结束，被信号终止\n");
		}
	}
}
