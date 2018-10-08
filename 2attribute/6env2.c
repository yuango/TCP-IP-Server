
#include <stdio.h>

extern char **environ;// 形参就是一个数组

int main()
{
	int i;
	for(i=0;environ[i]!=NULL;i++)
	{
		puts(environ[i]);
	}
}
