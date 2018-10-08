#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	puts("hello");//1次
	fork();//克隆进程
	puts("world");//2次
	printf("good");//内容先存到缓冲区，再显示，而不是直接输出到屏幕
	fork();//克隆进程和缓冲区的内容
	printf(" luck\n");//存到缓冲区,good luck 显示4次
}
