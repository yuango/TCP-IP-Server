#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	mkdir("mydir",0755);//建立目录
	chdir("mydir");//进入目录
	char buf[100];
	getcwd(buf,sizeof(buf));//获取当前目录绝对路径
	puts(buf);
	chdir("..");//退到上级目录
	sleep(5);//wait for 5 seconeds
	rmdir("mydir");//删除空目录
}
