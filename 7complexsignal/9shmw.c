#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
	int id = shmget(0x8888,100,IPC_CREAT|0644);
	printf("id=%d\n",id);
	char *p = shmat(id,NULL,0);//挂接,系统自动寻找本进程的可挂接内存地址。实际上对这个地址指向内容的操作就是对原共享内存的操作
	if(p==(char *)-1)//失败
	{
		perror("shmat failed");
		return -1;
	}
	strcpy(p,"yuange welcome");//在这段共享内存中存内容，如果其他进程也挂接了0x8888这个位置的内存，那么就能从中读取存在其中的内容
	shmdt(p);//解除挂接
}
