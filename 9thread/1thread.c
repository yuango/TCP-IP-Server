#include <pthread.h>
#include <stdio.h>
//支线程打点，主线程打*并输出x值。主线程结束整个程序就结束
void *func(void *p)
{//多线程执行无先后顺序
	*(int *)p = 200;//强转p类型为(int *)会修改x中的内容
	int i;
	for(i=0;i<20;i++)
	{
	  write(1,".",1);
	  sleep(1);
	}
	return (void *)8888;//c语言中常见类型强转,这里并不代表地址，还是表示数据
}

int main()
{
	pthread_t id;//保存线程id
	int x = 100;
	pthread_create(&id,NULL,func,&x);//创建一个新线程，运行func函数，x为功能函数带的形参
	int i;
	for(i=0;i<10;i++)
	{
	  write(1,"*",1);
	  sleep(1);
	}
	printf("x=%d\n",x);//x值被支线程改变
	void *retval;
	puts("等待辅助线程结束");
	pthread_join(id,&retval);//等待某个线程结束,func()返回值存入retval中
	printf("返回值：%d\n",(int)retval);//将(void *)8888强制转换类型为(int)8888
}
