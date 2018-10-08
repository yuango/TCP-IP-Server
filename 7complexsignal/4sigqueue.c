#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void func(int sig,siginfo_t *info,void *p)//info是用来获取信息的
{
	printf("收到信号,来自用户%d的进程%d,附带参数为%d\n",info->si_uid,info->si_pid,info->si_value.sival_int);//si_value类型为sigval_t,定义为typedef union sigval{ int sival_int;void *sival_ptr} sigval_t;
}

int main()
{
	struct sigaction act;
	struct sigaction oldact;
	act.sa_sigaction = func;//设置带参信号处理函数，函数名就是该函数首地址
	sigemptyset(&act.sa_mask);//无需屏蔽信号
	act.sa_flags = SA_SIGINFO;//用带参处理信号函数
	sigaction(SIGUSR2,&act,NULL/*&oldact*/);//登记信号处理,与signal(信号，func)区别就是可带参数，可恢复原来处理方式
	if(fork()==0)
	{//子进程结束会向父进程发送SIGCHLD信号
		printf("uid=%d,pid=%d\n",getuid(),getpid());
		union sigval v;
		v.sival_int = 2017;//设置要传递的参数
		sigqueue(getppid(),SIGUSR2,v);//给父进程发送带参数的信号
		sleep(1);
	}
	else
	{//父进程可以做自己的事
		pause();
	}
}
