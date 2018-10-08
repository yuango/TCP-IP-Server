
#include <stdio.h>

void f1()__attribute__((constructor));//used before main
void f2()__attribute__((destructor));//used after main

int main()
{
	puts("main function()");
}

void f1()
{
	puts("before main");
}

void f2()
{
	puts("after main");
}
