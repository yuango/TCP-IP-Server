#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	if(argc != 2)//没有文件或目录
	{//格式 ‘%s’ expects argument of type ‘char *’
		printf("%s 文件或目录路径\n",argv[0]);
		return 0;
	}
	struct stat s;//注意为什么不能定义结构*s
	if(lstat(argv[1],&s)!=0)
	{//failed
		puts("not exist!");
		return 1;
	}
	if(S_ISREG(s.st_mode))	puts("普通文件");//return 0 success
	else if(S_ISDIR(s.st_mode)) puts("目录");
	else if(S_ISLNK(s.st_mode)) puts("符号链接");
	else puts("其他");
	printf("权限:%o\n",s.st_mode&0777);//8进制 %o,取低9位
}
