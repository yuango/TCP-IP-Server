#include<string.h>

double gvar=123.45;

void i2str(int d,char *str)
{
	int i=0;
	if(d < 0)
	{
		d = -d;
		strcpy(str,"-");//copy '-' to str
		++str;
	}	

	while(d)
	{
		str[i++] = d%10+'0';//依据str首地址变化
		d /= 10;
	}

	if(i == 0)
	{
		strcpy(str,"0");
	}
	else
	{
		for(int j=0;j<i/2;j++)
		{
			char t = str[j];
			str[j] = str[i-1-j];
			str[i-1-j] = t;
		}
		str[i] = '\0';
	}
}
