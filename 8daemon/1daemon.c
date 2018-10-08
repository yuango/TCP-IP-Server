#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <pwd.h>
//getpwuid(uid)获取uid的详细信息
int main()
{
	daemon(0,0);//把进程设置为服务(精灵)进程,设置当前目录为根目录，关闭终端文件
	chdir(getpwuid(getuid())->pw_dir);//设置自己的主目录为当前目录,数据类型可man查看
	char c = 'A';
	for(;;)//服务进程一直运行
	{
	  int fd = open("letter",O_RDWR|O_CREAT,0600);//一般在主目路下都能成功
//	  char c = 'A';
	  write(fd,&c,1);
//	  if(++c>'Z')
//		c = 'A';
	  lseek(fd,0,SEEK_SET);//定位
	  read(fd,&c,1);
	if(++c>'Z') c = 'A';
	  close(fd);
	  sleep(1);
	}
}
