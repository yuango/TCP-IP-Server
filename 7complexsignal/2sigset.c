#include <signal.h>
#include <stdio.h>

int main()
{
	sigset_t ss;
	sigemptyset(&ss);//清空表示对所有信号都不阻塞sigfillset(&ss);//填满表示都阻塞
	puts(sigismember(&ss,SIGINT)?"sigint":"noint");//no
	sleep(2);
	sigaddset(&ss,SIGINT);
	puts(sigismember(&ss,SIGINT)?"sigint":"noint");//int
	sleep(2);
	sigdelset(&ss,SIGINT);
	puts(sigismember(&ss,SIGINT)?"sigint":"noint");//no
	sleep(2);
	sigfillset(&ss);
	puts(sigismember(&ss,SIGINT)?"sigint":"noint");//int


}
