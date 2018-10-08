#include <stdio.h>
#include <string.h>
int main(int argc,char *argv[],char *env[])
{//env是环境变量字符串数组，以NULL为结束符
	int i;
	char *p = NULL;
	for(i=0;env[i]!=NULL;i++)
	{
		puts(env[i]);//env[i]为地址指向环境变量,可以查看puts函数的参数类型为char *
		if(strncmp(env[i],"LANG=",5)==0)
		{
			p = env[i]+5;
		}
	}
	if(p!=NULL)
		printf("env LANG=%s\n",p);
//	p = NULL;
}
