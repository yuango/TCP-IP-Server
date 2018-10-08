#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//exec系列函数头文件

int main()
{
	char *argv[]={
		"/bin/ls",//规范写命令带路径
		"-l",
		"-d",
		"/bin",
		NULL//指针数组需要一个NULL作为结束元素
	};
	puts("execute ls -l -d /bin");
//	execv("/bin/ls",argv);//命令所在文件路径
execvp("ls",argv);//加上p表示通过环境变量取寻找可执行文件
//execl("/bin/ls","/bin/ls","-l","-d","/bin",NULL);
	puts("-------ERROR-------");//如果execv加载成功则不会再继续下面的程序，相反失败才会执行原进程中的程序

}
