
#include <stdio.h>
#include <stdlib.h>

int main()
{
	putenv("CLASS=jy0316");
	char *p = getenv("CLASS");
	if(p)
		puts(p);
	setenv("NAME","yuange",1);
	p = getenv("NAME");
	if(p) puts(p);
}
