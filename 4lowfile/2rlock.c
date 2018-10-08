#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd = open("1lseek.c",O_RDONLY);
	if(fd<0)
	{
		perror("open failed");
		return -1;
	}
	struct flock pos;
	pos.l_type = F_RDLCK;//读锁
	pos.l_whence = SEEK_SET;//参考点文件头
	pos.l_start = 19;//相对文件头偏移量19字节
	pos.l_len = 17;//加锁长度17字节
	if(fcntl(fd,F_SETLK,&pos)==-1)
	{
		perror("lock failed");
		return -1;
	}
	puts("lock success");
	sleep(5);//访问文件中加锁位置的内容
	pos.l_type = F_UNLCK;//unlock
	fcntl(fd,F_SETLK,&pos);//unlock
	puts("unlock success");
	close(fd);
}
