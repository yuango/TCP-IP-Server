#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{//父子进程一起运行
	if(fork()==0)//这里如果用vfork创建子进程但不克隆，需要紧跟(之间不加任何代码)exec系列函数
	{
	  execl("./child","child","yuange iloveu",NULL);//child程序内部循环输出argv[1]
	  puts("加载程序child失败");
	  exit(-1);
	}
	else
	{
		for(;;)
		{
		  write(STDOUT_FILENO,"*",1);
		  sleep(1);
		}
	}
}
