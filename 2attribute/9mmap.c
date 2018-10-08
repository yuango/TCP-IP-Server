
#include <stdio.h>
#include <sys/mman.h>

int main()
{
	char *p = mmap(NULL,200,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
	if(p!=MAP_FAILED)
	{
		scanf("%[^\n]",p);//scanf接口函数应该在定义时确定了enter键结束输入
		printf("你输入的的是:%s\n",p);
		munmap(p,200);
//		*p='a';//此时再使用就会段错误
	}
}
