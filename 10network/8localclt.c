#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
//本地套接字实现广播
int main()
{
	int fd = socket(AF_LOCAL,SOCK_STREAM,0);
	struct sockaddr_un s;
	s.sun_family = AF_LOCAL;
	strcpy(s.sun_path,"yoyo");
	if(connect(fd,(struct sockaddr *)&s,sizeof(s))<0)
	{
	  perror("connect falied");
	  return -1;
	}
	for(;;)
	{
	  char line[1000];
	  int n = read(fd,line,sizeof(line)-1);
	  if(n<=0) break;//出错或者读完就关闭
	  line[n] = '\0';
	  puts(line);
	}
	close(fd);
}
