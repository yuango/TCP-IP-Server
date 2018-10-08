#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>//file control

int main(int argc,char *argv[])
{
	if(argc!=3)//没有输入文件时
	{
		write(1,"a.out oldfile newfile\n",22);//1是标准输出文件即终端屏幕
		return 0;
	}
	int fd1 = open(argv[1],O_RDONLY);//只读
	int fd2 = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);//只写，如果没有就新建文件，截断
	if(fd1<0||fd2<0)//打开文件失败,不能用！=0来判断，因为fd成功是非负整数
	{
		perror("open failed");
		return -1;
	}

//正常工作状态
	int n;
	char buf[1024];
	while((n=read(fd1,buf,sizeof(buf)))>0)//返回读取的字节数，但当返回0时表示读到末尾，-1失败
	{
		int i;
		for(i=0;i<n;i++)//加密
		{
			buf[i]=~buf[i];//取反
		}
		write(fd2,buf,n);//n为读取de字节数正好用
	}
	close(fd1);
	close(fd2);//用完关闭
}
