#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("input %s path",argv[0]);
		return 0;
	}
	struct stat s;
	if(lstat(argv[1],&s)!=0)
	 {
		puts("not exist");
		return 1;
	 }			//将argv[1]的状态存在结构体中
	printf("硬连接%d,用户名%s,字节数%lu\n",s.st_nlink,getpwuid(s.st_uid)->pw_name,s.st_size);//getpwuid返回值为结构指针，而在结构体passwd中char *pw_name为指针类型，所以使用“->”来引用成员变量，且最终对指针类型为char *对应格式%s要求
}
