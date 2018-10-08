#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main()
{
	struct winsize w;
	for(;;)
	{
		ioctl(STDIN_FILENO,TIOCGWINSZ,&w);//0标准输入文件
		printf("%d行,%d列\n",w.ws_row,w.ws_col);
		usleep(2000000);//微秒,2s
	}
}
