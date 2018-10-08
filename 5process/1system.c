#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("hello,kitty\n");
	system("echo $PS1");
//	if(access("a.out",F_OK)==0)
//		system("./a.out");
	system("ls -l|wc -l>abc");//wc:word count统计单词个数后数据流重定向存到abc中,-l统计行数,这里是先建立了文件abc再wc -l?
	printf("hello world\n");
}
