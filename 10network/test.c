#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
//普通文件的读写，如果文件内容为空读函数返回值为0，对同一个文件读写函数相互影响下次动作的文件位置
int main()
{
	char buf[100];
	int fd = open("kiki",O_RDWR|O_CREAT,0644);
	if(fd==-1) {perror("open");return -1;}
	int n = read(fd,buf,sizeof(buf));
printf("%d",n);
	if(n<=0)
	{
		puts("NULL");
		return;
	}
}
