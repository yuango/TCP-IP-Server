#include <sys/time.h>
#include <signal.h>
#include <stdio.h>

void timeout()
{
	puts("time out");
}
int main()
{
	signal(SIGALRM,timeout);//使用那种信号有规定
	struct itimerval iv;
	iv.it_value.tv_sec=5;//第一次定时5秒
	iv.it_value.tv_usec=0;
	iv.it_interval.tv_sec=10;//以后定时每10秒一次
	iv.it_interval.tv_usec=0;
	setitimer(ITIMER_REAL,&iv,NULL);//实时时钟定时器，新值，旧值不需要
	for(;;)//定时到才跳出，时钟中断
	{
		write(1,".",1);
		sleep(1);
	}
}
