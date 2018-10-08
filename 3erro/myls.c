#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>

void printtype(int mode)
{
	if(S_ISREG(mode)) putchar('-');
	else if(S_ISDIR(mode)) putchar('d');
	else if(S_ISLNK(mode)) putchar('l');
	else if(S_ISFIFO(mode)) putchar('p');
	else if(S_ISSOCK(mode)) putchar('s');
	else if(S_ISCHR(mode)) putchar('c');
	else if(S_ISBLK(mode)) putchar('b');
	else putchar('@');
}

void printaccess(int mode)
{
	char *acc="rwx";
	int i;
	for(i=0;i<9;i++)
	{
		putchar(mode&0400?acc[i%3]:'-');
		mode=mode<<1;//mode<<=1
	}	
}

void showdetail(const char *name)
{
	struct stat s;
	lstat(name,&s);//取得name详细信息存在s中
	printtype(s.st_mode);//文件类型
	printaccess(s.st_mode&0777);//0777的0表示8进制，权限
	printf("%2d",s.st_nlink);
	printf("%7s",getpwuid(s.st_uid)->pw_name);
	printf("%7s",getgrgid(s.st_gid)->gr_name);
	printf("%10lu",s.st_size);//%Lu:long long unsigned
	char buf[20];
	strftime(buf,sizeof(buf),"%F %T",localtime(&s.st_mtime));
	printf("%20s %s\n",buf,name);
}

void listdetail(void)
{
	DIR *p = opendir(".");
	if(NULL == p)
	{
		perror("opendir");
		return;
	}
	struct dirent *q = NULL;
	while((q=readdir(p))!=NULL)
	{
		if(q->d_name[0]=='.') continue;//跳过本次循环
		showdetail(q->d_name);
	}
}

int main(int argc,char *argv[])
{
	if(argc>2)
	{
		printf("%s [direction]\n",argv[0]);
		return 0;
	}
	if(argc==2)
	{
		if(chdir(argv[1])!=0)//进入目录
		{
			perror("failed");
			return -1;
		}
	}//argc=1时不用动作，本身就在当前目录下
	listdetail();
}
