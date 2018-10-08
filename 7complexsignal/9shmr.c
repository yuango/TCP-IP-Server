#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
//在进程间通信不占用磁盘空间，在内存中运行较快
int main()
{
	int id = shmget(0x8888,0,0);//取得共享内存对象，不关心大小和权限,指定0x8888这个内存位置
//	printf("id=%d\n",id);
	if(id==-1)
	{
		perror("shmget failed");
		return -1;
	}
	char *p = shmat(id,NULL,SHM_RDONLY);//挂接成只读
	if(p==(char *)-1)
	{
		perror("shmat failed");
		return -1;
	}
//	strcpy(p,"yuange welcome");
	puts(p);//读取共享内存中的内容，实现进程通信
	shmdt(p);//解除挂接
	shmctl(id,IPC_RMID,NULL);//控制函数删除命令
}
