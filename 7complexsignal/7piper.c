#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
	char name[20];//进程间传输不能用指针，指针都是用的虚拟地址，在不同进程间不固定
	int age;
	double weight;
} Person;

int main()
{
//printf("%d\n",sizeof(Person));
//	mkfifo("pipe",0644);//建立一个管道文件,如果文件存在则跳过创建
	int fd = open("pipe",O_RDONLY);
	if(fd<0)
	{
		perror("open failed");
		return -1;
	}
	puts("打开成功");
//	printf("请输入姓名、年龄和体重：\n");
	Person x;
//	scanf("%s%d%lf",x.name,&x.age,&x.weight);
//	write(fd,&x,sizeof(x));//写入成功也可以做个判断
	if(read(fd,&x,sizeof(x))!=sizeof(x))//读32位
	{
		perror("read failed");
		return -1;
	}
	printf("姓名：%s\n年龄：%d\n体重：%gkg\n",x.name,x.age,x.weight);
	close(fd);//当管道文件同时存在读写双方是才会继续打开动作
//	unlink("pipe");//删除管道文件
}
