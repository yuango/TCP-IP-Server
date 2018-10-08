#include <sys/ipc.h>//进程间通信都用到的头文件
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>//随机函数
#include <time.h>

int main()
{
	int id = semget(0x7777,1,IPC_CREAT|0644);
	if(id==-1)
	{
	  perror("semget fialed");
	  return -1;
	}
	semctl(id,0,SETVAL,5);//每个信号量都是一个计数器，这里设置信号量的值为5用来计数
	int i;
	for(i=0;i<10;i++)
	{//产生10个子进程，但目的每次只有5个(信号量值指定)进程同步工作
	  if(fork()==0)
	  {
		struct sembuf sb;
		sb.sem_num = 0;
		sb.sem_op = -1;//
		sb.sem_flg = SEM_UNDO;//进程结束时，系统自动恢复该进程对信号量的操作(-1操作会被恢复即加1)
		while(semop(id,&sb,1)==-1)//进程对信号量进行-1操作，期间肯让你个会被打断，所以用循环来防止被打断带来的影响
		{//在子进程访问资源前，进来-1操作，当不够减(值减到了0)时会等待，这样就不能继续下去访问资源。只有-1操作被恢复(值够减>0)时才能有新进程进来访问资源，这样就实现了控制多进程同步

		}
		srand(getpid());//以进程id值作为种子产生随机数,rand()的产生值依赖于次
		printf("%d子进程开始工作\n",getpid());
		sleep(rand()%16+5);//5~20s,rand()取得0～1
		printf("%d子进程工作完毕\n",getpid());

		sb.sem_op = 1;//手动恢复该子进程对计数器(信号量)的-1操作
		semop(id,&sb,1);
		exit(0);
	  }
	}
	//父进程等待子进程全部结束wait函数，子进程没有结束时一直阻塞等待，一旦有结束的wait返回值必然不是-1,这时会while循环，直到没有子进程(子进程全部结束了)，这时wait函数才会失败返回-1。(总的来说看wait函数什么时候会失败，有子进程没有结束时会一直等待，有子进程结束时返回子进程id，所以只有没有子进程可结束时会失败)
	while(wait(NULL)!=-1);//有子进程结束时wait函数返回进程id，失败返回-1.如果全部子进程都结束(则wait函数必然返回-1因为没有子进程了)就结束while循环(否则一直阻塞等待),并释放子进程资源(不然会成为僵尸进程)。NULL表示不保存子进程结束状态信息
	puts("全部子进程都结束");
	semctl(id,0,IPC_RMID,NULL);//删除信号量集
}
