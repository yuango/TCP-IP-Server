#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
	umask(0);
	int fd = open("mmap",O_RDWR|O_CREAT,0644);
	if(fd<0)
	{
		perror("open failed");
		return -1;
	}
	ftruncate(fd,1024);//截断成1k长
	char *p = mmap(0,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);//映射后的地址
	if(p==MAP_FAILED)
	{
		perror("mmap failed");
		return -1;
	}
	for(;;)
	{
		int n = read(STDIN_FILENO,p,1024);//从标准输入文件(键盘)读数据存到p指向的内存中，最大存1K字节
		if(n<=0) break;//n=-1失败，n=0读取结束,都结束循环
	}
	munmap(p,1024);
	close(fd);
}
