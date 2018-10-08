#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
//ip地址格式转换
int main()
{
	in_addr_t nip;//内部格式ip地址，实际为无符号32位整数
	char sip[16];//点分十进制格式ip地址存放到字符串数组中
	inet_pton(AF_INET,"192.168.1.10",&nip);
	unsigned char *p = (unsigned char *)&nip;//???取首地址，char型相当于整型，占一个字节为8位(在0~255范围内char型和int型是通用的存储方式)
	int i;
	for(i=0;i<4;i++)
	{//这里输出的是网络字节顺序
	  printf("%02x ",*p++);//每次输出一个字节，以16进制输出，也可以用%d以10进制输出
//	printf("%d ",*p++);
	}
	printf("\n");
	inet_ntop(AF_INET,&nip,sip,sizeof(sip));//指定数组长度
	puts(sip);
}
