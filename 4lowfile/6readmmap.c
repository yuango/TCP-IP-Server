#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd = open("mmap",O_RDWR);
	if(fd < 0)
	{
		perror("open failed");
		return -1;
	}
	char *p = mmap(0,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(p==MAP_FAILED)
	{
		perror("mmap failed");
		return -1;
	}
	int cnt = 0;//计时器
	for(;;)//如果不加延时和定时结束，共享很烧cpu
	{
		if(p[0]!='\0')//有字符串内容
		{
			printf("%s",p);//输出整个字符串
printf("长度1:%d字节\n",strlen(p));
			memset(p,0,strlen(p));//p指向的内存前strlen(p)(为整个字符串长度)字节全写0，返回指针p(输出完之后就清零)
printf("长度2:%d字节\n",strlen(p));

			cnt=0;
		}
		else
		{
			if(++cnt==20)
				break;
		}
		usleep(500000);
	}
	munmap(p,1024);
	close(fd);
}
