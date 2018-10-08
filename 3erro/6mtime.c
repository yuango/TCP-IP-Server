#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
int main(int argc,char *argv[])
{
	char buf[100];
	if(argc!=2)
	{
		puts("a.out path");
		return 0;
	}
	struct stat s;
	if(lstat(argv[1],&s)!=0)
	{
		puts("NOT exsit!");
	}
	else
	{
		strftime(buf,sizeof(buf),"最后修改时间:%F %T",localtime(&s.st_mtime));
	puts(buf);
	}
}
