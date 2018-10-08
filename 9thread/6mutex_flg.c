#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
//利用互斥锁和条件变量可以实现工作控制
int flag = 0;
//pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m;//必须放在最开头声明
void *thread(void *p)
{
  for(;;)
  {//互斥锁加标志判断有诸多好处，但是也有坏处:vflag为假时，辅助进程会一直循环加锁解锁，将导致cpu负载过重
	pthread_mutex_lock(&m);
	int vflag = flag;//尽量加锁期间短(所以不宜加延时),防止错过条件满足的情况
	pthread_mutex_unlock(&m);
	if(vflag)
	{
	  write(1,p,1);//c语言中void *类型可以和其他任意类型直接赋值，不许要转换类型，而c++中必须强转类型
//	  printf("本线程id=%d\n",(int)pthread_self());
	  sleep(1);
	}
  }
}
int main()
{
	pthread_mutex_init(&m,NULL);
	pthread_t id1,id2;
	pthread_create(&id1,NULL,thread,".");
	pthread_create(&id2,NULL,thread,"*");
	for(;;)
	{
	  char c;
//	  printf("please input a word\n");
	  scanf(" %c",&c);//开头跳过空格和换行符等无用字符,%c会接收所有字符(包括空格等).也可以防止其他输入问题
if(c=='q') return 0;
	  pthread_mutex_lock(&m);
	  flag = (c=='a');//flag是全局变量，三个线程都会操作它，所以主线程也要加互斥锁
	  pthread_mutex_unlock(&m);
	}
}
