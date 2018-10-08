#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
//	umask(0);//不屏蔽任何权限
	int fd = open("id",O_RDWR|O_CREAT,0666);
	if(fd<0)
	{
		perror("open failed");
		return -1;
	}
	unsigned int id = 0;//4byte
	read(fd,&id,sizeof(id));//从文件中读取4字节内容，存到id中
	id++;
	lseek(fd,0,SEEK_SET);//lseek(fd,-4,SEEK_CUR)
	write(fd,&id,sizeof(id));//将id的值写到文件中
	printf("id=%u\n",id);
	return 0;
}
