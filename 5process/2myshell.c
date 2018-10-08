#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//每次调用函数system()都是不同的bash来执行，所以局部环境变量只对当前进程有效，再次调用system就不可用了.那么在使用命令改变环境变量时，就不要调用system而是在本进程内处理命令(利用接口函数自编处理命令)

int isvar(const char *begin,const char *end)
{
	const char *p;
	char s;
	for(p=begin;p<end;p++)
	{
		s = *p;
		if((s!='_') && (!((s>='a')&&(s<='z'))) && (!((s>='A')&&(s<='Z'))))
			return 1;
	}
	return 0;
}

int main()
{
	puts("welcom to use my shell!");
	char cmd[256];
	char *p=NULL;
	for(;;)
	{
		printf("ys> ");
		scanf(" %[^\n]",cmd);//空表示跳过任意多空白字符，直到遇到非空白为止。读入字符串直到读到\n为止
		if(strcmp(cmd,"exit")==0)
		{
			puts("thank you for using my shell!byebye");
			break;//跳出死循环继而执行下面的程序，也可以用 return 来直接结束main函数
		}
//处理cd 命令和设置环境变量命令PATH=
		if(strncmp(cmd,"cd ",3)==0)
		{
		  if(chdir(cmd+3)!=0)//接口函数chdir可以以绝对路径进入页可以相对路径进入，函数内部应该封装好了
			perror("enter failed");//改变当前目录为指定的路径的目录，那么就不需要调用system函数了
		}
		else if(p=strchr(cmd,'='))//isvar()判断等号左边是否是变量名,strchr没找到返回NULL
		{
		  if(!(isvar(cmd,p)))
		  {
			*p = '\0';//切割字符为两串，此时p指向等号的地址,cmd遇到'\0'字符串结束，即cmd就为变量名而p之后的字符串内容就是要设定的环境变量值
			setenv(cmd,p+1,1);
		  }
		  else
		  {
                        puts("the variable name is illegal! write again");
			continue;
		  }
		}
		else
			system(cmd);
	}
}
