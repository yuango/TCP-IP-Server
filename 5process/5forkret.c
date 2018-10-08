#include <stdio.h>
#include <unistd.h>

int main()
{//即使在判断语句里，函数还是会先执行再判断
	if(fork()==0)//这里返回值为0时必然是克隆进程后的子进程
	{
		printf("子进程%d,父进程%d\n",getpid(),getppid());
	}
	else//如果fork返回-1说明克隆进程失败，克隆成功的返回值为子进程id，但是必然不是0
	{
		printf("父进程%d,父父进程%d\n",getpid(),getppid());//经过测试，如果父进程这里不加延时，那么父进程可能会先结束，使得子进程变成孤儿
		usleep(100000);
	}
	puts("hello");//不用带\n，自带换行
}
