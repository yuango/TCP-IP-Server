#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>//缺少会exit警告不兼容

int main()
{
	int i;
	char *s = "abcdefg";
	for(i=0;i<3;i++)//根据以下功能，最终只有三个子进程共一个父进程
	{
		if(fork()==0)//子进程进来执行
		{
			int j;
			for(j=0;j<15;j++)
			{
				write(STDERR_FILENO,s+i,1);//3个子进程每个输出的字符不同，分别是a,b,c
				sleep(1);
			}
			exit(10+i);//结束当前进程，即子进程都会在这里结束
		}//父进程会继续下一次循环
	}
//父进程会继续执行到这里并向下执行
	int info;
	for(;;)
	{
//		pid_t child = wait(&info);//进入等待就什么都干不了，子进程结束之前下面的不能执行。这时只有在子进程都结束后父进程才会动作。waitpid可以不等待
		pid_t child = waitpid(-1,&info,WNOHANG);//任意子进程不等待,可以继续执行下面内容。这时父进程就可以和子进程一起动作
		if(child==-1) break;//一直循环到没有子进程就跳出循环
		if(child!=0)//返回0时表示子进程没有结束
			printf("子进程%d结束\n",child);
		write(STDERR_FILENO,".",1);//用wait在子进程结束才会输出.，而在waitpid时子进程没有结束时也会输出'.'。
		sleep(1);
	}
	puts("全部子进程结束");
	pause();//暂停直到遇到...便于查看子进程状态
}
