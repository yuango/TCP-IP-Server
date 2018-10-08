#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

typedef struct Msg{//消息由两部分组成：类型和数据，收发消息都是针对数据
	long type;
	char name[20];
	int age;
	float score;
} msg;

int main()
{
	int id = msgget(0x9999,IPC_CREAT|0600);
	printf("id=%d\n",id);
	if(id==-1)
	{
		perror("msgget failed");
		return -1;
	}
	msg m;
	printf("please input type,name,age and score:\n");
	scanf("%ld%s%d%f",&m.type,m.name,&m.age,&m.score);
	msgsnd(id,&m,sizeof(m)-sizeof(long),0);//发送的是数据，所以大小不应该包含类型长度，而错误就出现在把数据越界保存到类型中
}
