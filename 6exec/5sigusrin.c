#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

int main()
{
	pid_t who;
	printf("please input pid:");
	scanf("%d",&who);
	char buf[100];
	for(;;)//从键盘输入字符串
	{
	  printf("input:");
	  scanf(" %[^\n]",buf);//跳过空白字符，读取一串字符直到换行为止.自带字符串结束符
	  int fd;
	  for(;;)//按要求打开文件，直到成功打开为止
	  {
		  fd = open("data",O_WRONLY|O_CREAT|O_EXCL,0644);//只读/创建/必须新建(文件存在就失败)，文件存在说明没取走
	  	  if(fd>=0) break;//打开文件成功就跳出继续下面动作
		  puts("file existed");
		  sleep(1);//文件存在就等待继续循环
	  }
	  write(fd,buf,strlen(buf));//将读取的字符串存入文件data中
	  close(fd);
	  kill(who,SIGUSR1);//向进程发送自定义信号
	  if(!strcmp(buf,"q")) raise(SIGTERM);
	}
}
