#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
//利用互斥锁和条件变量可以实现工作控制
int flag = 0;
pthread_mutex_t m;//必须放在最开头声明
pthread_cond_t c = PTHREAD_COND_INITIALIZER;//条件变量初始化
void *thread(void *p)
{
  for(;;)
  {
	pthread_mutex_lock(&m);
	if(flag==0)//如果有处理信号，为了防止被信号打断等待，这里应该用while更严谨
	{//这样就不会一直循环加锁解锁，占用过多cpu
	  pthread_cond_wait(&c,&m);//进入等待，自动解锁了互斥量，等到通知后加锁互斥量，结束等待返回
	}
	pthread_mutex_unlock(&m);
	write(1,p,1);
	sleep(1);
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
	  char ch;
	  scanf(" %c",&ch);
if(ch=='q') return 0;
	  pthread_mutex_lock(&m);
	  if(ch=='a')
	  {//如果连续输入两次a，那么两个线程都会得到通知(因为本例陈只有两个辅助线程)
		flag = 1;
		pthread_cond_signal(&c);//只任意通知到一个线程
	  }
	  else if(ch=='b')
	  {
		flag = 1;
		pthread_cond_broadcast(&c);//广播通知到所有线程
	  }
	  else
		flag = 0;//这里就不能发送通知了，没有通知，辅助线程就会等待
	  pthread_mutex_unlock(&m);
	}
}
