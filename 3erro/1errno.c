#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
	FILE *fp = fopen("furong","quange");//man fopen查看定义类型为FILE 参数为文件路径和打开模式方式
	if(fp==NULL)//失败有错误码errno
	{
		printf("open file furong failed!\n");
		if(errno==EINVAL)
			printf("打开方式无效\n");
		printf("errno=%d\n",errno);
		printf("%s\n",strerror(errno));//错误码对应对字符串
		perror("错误信息");//打印当前错误信息
		printf("error string:[ %m]\n");//打印当前错误信息
	}
}
