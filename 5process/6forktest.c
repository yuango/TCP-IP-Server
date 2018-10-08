#include <stdio.h>
#include <unistd.h>
//孤儿进程测试,所有孤进程都会被初始化进程接收
int main()
{
	int i;
	if(fork()==0)//子进程
	{ 
	  for(i=0;i<10;i++)
	  {
		printf("进程id:%d,父进程%d\n",getpid(),getppid());
		sleep(1);
	  }
	}
	else
	{
	  for(i=0;i<3;i++)
	  {
		printf("我是父进程%d\n",getpid());
		sleep(1);
	  }
	}
	
}
