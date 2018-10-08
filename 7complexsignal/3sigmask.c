#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	printf("pid=%d\n",getpid());
	sigset_t newset;
	sigset_t oldset;
	sigemptyset(&newset);
	sigaddset(&newset,SIGINT);//ctrl+c
	sigaddset(&newset,SIGTERM);//kill -9
	sigprocmask(SIG_BLOCK,&newset,&oldset);//设置屏蔽，保存旧值
	puts("睡眠中勿扰");
	sleep(10);
	puts("睡醒了");
//取得处于未处理状态的信号集，把信号集存到tmp中
	sigset_t tmp;
	sigpending(&tmp);
	puts(sigismember(&tmp,SIGINT)?"sigint":"noint");
	puts(sigismember(&tmp,SIGTERM)?"sigterm":"noterm");

	sigprocmask(SIG_SETMASK,&oldset,NULL);//在这里执行成功之后，如果有被阻塞的信号来过则直接执行信号处理，下面的就不会执行
	puts("没有信号来过");//如果这里执行了说明之前没有信号到来
}
