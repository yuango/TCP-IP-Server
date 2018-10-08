#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("1lseek.c",O_RDWR);//读写打开文件
	if(fd<0)//失败返回-1
	{
		perror("open failed");
		return -1;
	}
	struct flock pos;//设置锁结构体内容
	pos.l_type = F_WRLCK;//想要取得加锁信息需要尝试去加锁，成功后再解锁
	pos.l_whence = SEEK_SET;
	pos.l_start = 19;
	pos.l_len = 17;
	//pos.l_pid = -1;//用-1表示不存在的PID,自己会置成-1
	if(fcntl(fd,F_GETLK,&pos)==-1)//fcntl failed return-1
	{
		perror("getlock failed");
		return -1;
	}
	if(pos.l_type==F_UNLCK)//fcntl动作后，如果文件没有加锁，那么就会返回F_UNLCK给l_type,而结构体中的其他内容不变
	{
		puts("not lock yet");
	}
	else
	{
		puts("have been locked");
		printf("process i:%d\n",pos.l_pid);
		printf("lock type:%s\n",pos.l_type==F_RDLCK?"read lock":pos.l_type==F_WRLCK?"write lock":"unlock");
	}
}


