#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{//父子进程通过管道进行通信,实际父子进程处理同一个文件，父进程开写端，子进程开读端
	int fd[2];
	pipe(fd);//是同一文件
	char buf[100];
	if(fork()==0)
	{//只有一个子进程
puts("我是子进程我进来了");
		close(fd[1]);//关闭写端保留读段
		int n;
		while((n=read(fd[0],buf,sizeof(buf)))>0)//下次子程序会被阻塞在read函数这里
		{//n=0表示文件读完没有内容了
puts("子进程读到文件内容了");
		  int i;
		  for(i=0;i<n;i++)
		  {
			if(islower(buf[i]))//小写变大写
			  putchar(toupper(buf[i]));
			else if(isupper(buf[i]))//大写变小写
			  putchar(tolower(buf[i]));
			else
			  putchar(buf[i]);
		  }
puts("子进程没有跳出while循环");//子程序执行到这里后,循环去执行读函数(这就是为什么使用while而非if的原因,程序在这句执行完成后需要回头)，而如果管道中是空的(之前读过一次后管道缓存被清空直到下次再写入数据)那么读函数就会被阻塞等待标准输入文件有数据存入(即等待键盘输入)
		}
		close(fd[0]);//关闭读端，则关闭整个文件
puts("子进程结束了");
	}
	else
	{//父进程
puts("父进程进来了");
		int m;
		close(fd[0]);//关闭读端保留写端
		for(;;)
		{
		  m = read(STDIN_FILENO,buf,sizeof(buf));//标准输入端即从键盘输入，输入结束按下enter键后,将字符串存入buf，然后自动清空标准输入文件
printf("读出的字节数%d\n",m);//在从键盘输入字符串到标准输入文件中时，enter键的换行符也算作一个字符存入其中，所以子进程也会读这个换行符(比如单独只输入enter键,结果跳过2行)
		  if((m==2)&&(buf[0]=='q')) break;//退出
		  write(fd[1],buf,m);//如果管道缓冲区是满的(即数据还没有被读取),那么write函数会被阻塞，等待管道清空
		}
sleep(1);
puts("a");
		close(fd[1]);//这句执行之后子进程立即结束，说明匿名管道是父进程关闭读写端后，子进程就会退出read函数阻塞状态，跳出while循环
sleep(1);
puts("b");
puts("父进程结束了");
	}
}
