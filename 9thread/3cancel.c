#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void *thread(void *p)
{
	for(;;)
	{
	  printf("%s",(char *)p);//这里%s就是要求传char *类型
	  fflush(stdout);
	  sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t id;
	pthread_create(&id,NULL,thread,".");
	sleep(5);
	pthread_cancel(id);//请求终止指定id线程
	puts("------------------");
	sleep(5);
	pthread_exit(NULL);//终止本线程
	puts("******************");//不会执行
	return 0;
}
