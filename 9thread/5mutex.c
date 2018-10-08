#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
//功能类似银行窗口，每次只能服务一个人，且按号牌顺序接收服务.用互斥量加锁和解锁实现一次一人，完毕按顺序下一人
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;//初始化互斥量,注意互斥量声明应放在最开头
const char *list[10]={"Aa","Bb","Cc","Dd","Ee","Ff","Gg","Hh","Ii","Jj"};
int pos = 0;//关键数据，用互斥量控制对它的访问

void *func(void *p)
{//实际上每个线程都可以有不同的功能函数，本例是使用同一个func，但是对于全局变量每个线程都可以访问，也可以改变等动作。所以在互斥锁加上和解锁期间就可以限制只有一个线程可以访问pos和改变pos
  for(;;)
  {
	pthread_mutex_lock(&m);//访问pos前先加锁互斥量,没解锁前其他线程执行到这里都会等待...互斥锁对于所有线程是共影响的
	if(pos>9) break;
	printf("%s号美女为%s服务\n",(char *)p,list[pos]);//这里访问的list[pos]指定的资源就被锁定，别的线程无法同时访问pos
	pos++;
	pthread_mutex_unlock(&m);//访问完毕pos解锁，这里之后下个线程才能访问pos，且pos是顺序递增的
	sleep(5);//模拟服务时间，可用随机量模拟。互斥锁期间只是为了唯一的顺序的取得pos，以下才是正真的处理工作
  }
  pthread_mutex_unlock(&m);//队列空，就解锁互斥量
}
int main()
{
	int a[10];
//	pthread_mutex_init(&m,NULL);
//	pthread_mutex_lock(&m);
	pthread_t id1,id2,id3;//创建3个线程
	pthread_create(&id1,NULL,func,"1");
	pthread_create(&id2,NULL,func,"2");
	pthread_create(&id3,NULL,func,"3");
	pthread_join(id1,NULL);//等待线程结束，不关心返回值
	pthread_join(id2,NULL);
	pthread_join(id3,NULL);


}
