#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pwd.h>
//执行顺序d-a-b-uid-c
void func(int sig)
{
	puts("a");
	getpwnam("yuange");//函数返回结构指针，指向的结构体变量为静态局部变量，主函数与信号处理函数都调用了该函数，则主函数期待的结果就会被信号处理函数改变
	puts("b");
}

int main()//实际期望取得root的pid-0,实际取得用户yuange的pid-1000
{
	signal(SIGINT,func);
	struct passwd *p = getpwnam("root");//取得用户名信息
	puts("d");
	sleep(20);//被信号打断之后失败返回剩余秒数，继续执行下面内容
	printf("uid=%d\n",p->pw_uid);
	puts("c");
}
