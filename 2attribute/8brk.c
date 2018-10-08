
#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("pagesize:%d\n",getpagesize());
	int *p = sbrk(0);//返回当前终点，有效地址不包含终点
	printf("end:%p\n",p);
//	int n=*p;//不是有效地址，故段错误
	brk(p+8);//段结束地址后移8*4字节,操作系统会把扩展的这段虚拟内存映射到物理内存，但映射以页为基本单位，所以实际映射的内存会是一页(4k字节)。
	
	p = sbrk(0);//返回当前终点，有效地址不包含终点
	printf("end:%p\n",p);
	int i;
	for(i=0;i<18;i++)
		p[i]=10+i;//越界，但不会段错误
	for(i=0;i<18;i++)
		printf(" %d",p[i]);
	printf("\n");

	p = sbrk(0);//返回当前终点，有效地址不包含终点
	printf("end:%p\n",p);

//	p[1016]=111;//超越内存页，才会段错误(p[0]为原p+8位置)
	printf("end1:%p\n",sbrk(4070));//32+4070超过一页，再映射到下一页
	p[1016]=111;//正常
	sbrk(-6);//回退6字节，最后一页映射也就不需要来，操作系统会解除这一页映射
	p = sbrk(0);//返回当前终点，有效地址不包含终点
	printf("end:%p\n",p);

}
