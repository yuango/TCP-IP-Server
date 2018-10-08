#include <stdio.h>

typedef struct A
{
	char a;
	double b;
	char c;	
}A;//默认4字节对其，double 是8字节

typedef struct B
{
	char a;
	double b;
	char c;	
}__attribute__((packed)) B;//1字节对齐
//#pragma pack()恢复默认对齐补齐
#pragma pack(1)//预处理指令
typedef struct C
{
	char a;
	double b;
	char c;
}C;

typedef struct D
{
	char a;
	int b;
	char c;
}__attribute__((aligned(8))) D;//内部8字节补齐(aligned)不好用

int main()
{
	printf("sizeof A=%d\n",sizeof(A));
	printf("sizeof B=%d\n",sizeof(B));
	printf("sizeof C=%d\n",sizeof(C));
	printf("sizeof D=%d\n",sizeof(D));
	C x;//查看结构体及其成员地址关系
	printf("%p\n",&x);
	printf("%p\n",&x.a);
	printf("%p\n",&x.b);
	printf("%p\n",&x.c);
}

