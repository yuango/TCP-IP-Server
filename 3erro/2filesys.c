#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//rename,symlink,chmod,access,remove
int main(int argc,char *argv[])
{
puts(argv[0]);
if(strcmp(argv[0],"./lfr")!=0)//argv[0]指向运行的程序名
{
 if(strcmp(argv[0],"./furong")!=0)
 {	puts("命令既不是lfr也不是furong");//经测试这里字符串比较you用	
	rename(argv[0],"furong");//rename a.out to furong
	symlink("furong","lfr");
	chmod("furong",00555);
 }
}
	if(access("furong",F_OK)==0) 
		puts("furong exist");
	if(access("furong",R_OK)==0) 
		puts("read");
	if(access("furong",W_OK)==0) 
		puts("write");
	if(access("furong",X_OK)==0) 
		puts("excute");
}
