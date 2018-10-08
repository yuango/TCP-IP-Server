#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void f1(void)
{
	puts("f1()");
}

void f2(void)
{
	puts("f2()");
}

void f3(int n,void *p)
{
	printf("n=0x%x,p=%p\n",n,p);
	free(p);
//	printf("freep=%p\n",p);//p地址在释放前后相同，因为内存没有被使用
}

int onefunc()
{
	exit(0);//return 0 只能结束本函数不能使main函数结束，而exit(0)可以使整个进程都结束且返回值为0
}

int main()
{
	atexit(f1);
	atexit(f2);
	void *q = malloc(10);
	on_exit(f3,q);//程序正常结束后按登记顺序相反的顺序执行清理函数
	printf("groupid:%d\n",getpgid(getpid()));
	printf("mq=%p\n",q);
	onefunc();
//	return 0;
	puts("this is not happen\n");
}
