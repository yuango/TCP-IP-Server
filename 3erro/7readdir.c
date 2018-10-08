#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	DIR *p = opendir(".");
	if(NULL == p)
	{
		puts("文件不能为空");
		return 0;
	}
	struct dirent *q;
	while(NULL != (q=readdir(p)))//逐项读取，读完指向下一个地址,是readdir返回值在变,每读取一项后指向下一个地址项
	{
		if(q->d_name[0]=='.') continue;//跳过隐藏文件
		printf("%s\t",q->d_name);//d_name为字符型数组，相当于char *d_name
	}
//	printf("\n");
	closedir(p);
}
