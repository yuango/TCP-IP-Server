#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[])
{
	if(argv[1]==NULL) return 0;
	for(;;)
	{
	  write(STDOUT_FILENO,argv[1],strlen(argv[1]));//sizeof不行
	  sleep(1);
	}
}
