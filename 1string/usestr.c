#include <stdio.h>
#include <string.h>
#include "str.h"

int main()
{
	char str[20];
	int n;
	printf("please input a string and a number:\n");
	scanf("%s%d",str,&n);
	puts(str);
	strtoupper(str);
	puts(str);
	strtolower(str);
	puts(str);
	i2str(n,str);
	puts(str);
	printf("%g,%g\n",gvar,gvar+n);
}
