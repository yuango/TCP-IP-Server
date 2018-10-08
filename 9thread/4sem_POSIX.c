#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
//在多线程中使用信号量的计数，实现线程同步.每次输入一个新值，辅助线程都会立即排好序
//pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;//初始化互斥量
sem_t s;//全局变量写到main函数中也可以

void *func(void *p)
{
	int i;
	int *a = p;//强转p类型
	for(i=0;i<10;i++)
	{
//	  pthread_mutex_lock(&m);//已加锁就等待直到被解锁
	  sem_wait(&s);//等待主线程输入一个数据，使得计数器-1可减.每循环一次都要等待主线程输入，实现线程同步.没有这步初始化时也能正常工作，或许是系统自动初始化了
	  int tmp = a[i];
	  int j;//插入法排序
	  for(j=i;j>0&&tmp<a[j-1];j--)
	  {
		a[j] = a[j-1];//比较tmp与其前一位大小，小就将tmp置于空档a[j-1]处,a[j-1]向前移动一位
	  }
	  a[j] = tmp;//循环结束时tmp所处的空档位置
//	  for(j=0;j<i+1;j++)
//		printf("%d ",a[j]);
//	  puts("");
	}
}

int main()
{
	int a[10];
	sem_init(&s,0,0);//信号量存在s中，不在进程间通信，初始化信号量值(计数值)为0.则开始时辅助线程sem_wait只能等待
//	pthread_mutex_init(&m,NULL);
//	pthread_mutex_lock(&m);
	pthread_t id;
	pthread_create(&id,NULL,func,a);//创建线程
	int i;
	for(i=0;i<10;i++)
	{
	  printf("请输入第%d个数据",i+1);
	  scanf("%d",&a[i]);//a++也可以
	  sem_post(&s);//加1操作给辅助线程sem_wait放行
	}
	usleep(100);//延时等待最后一个数据排序完毕，不然可能直接执行下面的显示程序而没有排好序
	for(i=0;i<10;i++)
	{//辅助线程排序完成后显示
	  printf("%d ",a[i]);
	}
	printf("\n");
	sem_destroy(&s);//销毁信号量
//主线程结束时，整个程序就结束了，如果不需要辅助线程的返回值，不用特意手动结束线程
}
