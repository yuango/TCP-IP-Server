#include <stdio.h>
#include <dlfcn.h>
int main()
{
	printf("1-中文 2-english:");
	int sel;
	scanf("%d",&sel);
	void *handle;
	if(sel == 1)//动态库需要带上路径,or use export LD_LIBRARY_PATH=./,or put .so to /lib and /usr/lib
	{
		handle = dlopen("./libch.so",RTLD_NOW);
	}
	else
	{
		handle = dlopen("./liben.so",RTLD_NOW);
	}

	if(handle == NULL)
	{
		puts(dlerror());
		return -1;
	}

	void (*fp)(void);//函数指针，最终fp的地址是谁，fp()就执行该位置处的函数
	fp = dlsym(handle,"welcome");//在此之前之后都调用dlerror()来判断后一次的返回值是否非空，判断是否失败，是严谨做法

	if(fp == NULL)
	{
		puts(dlerror());
		return -1;
	}

	fp();//(*fp)()
	dlclose(handle);
}
