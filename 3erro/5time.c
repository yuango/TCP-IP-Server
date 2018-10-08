#include <stdio.h>
#include <time.h>

int main()
{
	time_t now = time(NULL);//NULL表示不把返回值存到地址
	printf("now=%lu\n",now);//unsigned long
	struct tm *p = localtime(&now);
	printf("%d年%d月%d日 星期%d %02d:%02d:%02d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday,p->tm_wday,p->tm_hour,p->tm_min,p->tm_sec);//%02d 中02表示宽度达到2列以上
	char buf[100];
	strftime(buf,sizeof(buf),"%F %w %T",p);//%F=%Y-%m-%d,%w,%T=%H-%M-%S,将分离时间按格式转成字符串放到buf中，返回字符串长度，所以可以调用buf中内容
	puts(buf);
}
