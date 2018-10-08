#include <stdio.h>
#include <pthread.h>

void *func(void *p)
{
	int i;
	int *a = (int *)p;
	for(i=0;i<20;i++)
	{
	  a[i] = 100+i;
	  sleep(1);
	}
	return NULL;
}

int main()
{
	int a[20];//main中也是全局的
	pthread_t id;
	pthread_create(&id,NULL,func,a);
	sleep(2);//先等待辅助进程先工作(但不一定，辅助线程页可能在此期间被打断而没有先工作)
	int i;
	for(i=0;i<20;i++)
	{
	  printf("%d ",a[i]);//printf()是把数据发送到缓冲区，只有遇到换行或者刷新缓冲区时才会输出到屏幕
	  fflush(stdout);//立即显示
	  sleep(1);
	}
}
