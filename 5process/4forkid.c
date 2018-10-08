#include <stdio.h>
#include <unistd.h>

int main()
{
	int id = getpid();
	fork();
	int newid = getpid();//这里父子进程都会执行，但是内存相互独立
	if(newid==id)
	{
		printf("father process id:%d\n",id);
//		usleep(10000);//在父进程这里如果不加延时，那么本机测试父进程会先结束，那么下面的子进程就会变成孤进程，此时试验结果子进程的父进程id就会变成1(初始化进程id)
		for(;;)
		{
			write(1,".",1);//屏幕输出用1或者2都可以，注意双引号(这里需要是地址而不能用单引号)
			sleep(1);
		}
	}
	else
	{
		printf("son id:%d,father id:%d\n",newid,getppid());//getppid()根据当前进程id取得相应父进程id
		for(;;)
		{
			write(2,"*",1);
			sleep(1);
		}

	}
}
