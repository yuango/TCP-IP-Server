#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

typedef struct Msg{
	long type;
	char name[20];
	int age;
	float score;
} msg;

int main()
{
	int id = msgget(0x9999,0);
	if(id==-1)
	{
		perror("msgget failed");
		return -1;
	}
	long type1;
	msg m;
	printf("请输入想要取得的消息类型:\n");
	scanf("%ld",&type1);
	if(msgrcv(id,&m,sizeof(m)-sizeof(long),type1,IPC_NOWAIT)==-1)//接收消息只是针对数据部分，所以数据大小应该出去类型大小
	{
		puts("没有这个类型的消息");
	}//接收到的消息存到结构体中
	else
	{
		printf("type:%ld\nname:%s\nage:%d\nscore:%g\n",m.type,m.name,m.age,m.score);//%g自动选择合适的格式，省去不必要的0
	}
}
