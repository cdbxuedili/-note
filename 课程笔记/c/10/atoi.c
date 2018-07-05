#include <stdio.h>
#include <string.h>

int my_atoi(const char *p);

int main(int argc, const char *argv[])
{
	char buf[128];
	int ret = 0;
	if(argc != 2)
	{
		printf("please input argv[1]!\n");
		return -1;
	}
	strcpy(buf,argv[1]);
	ret = my_atoi(buf);
	printf("ret:%d\n",ret);
	return 0;
}

int my_atoi(const char *p)
{
	int num = 0;
	while(*p != '\0')
	{
		if(*p >= '0' && *p <= '9')
		{
			num = num*10 + (*p - '0');
			p++;
		}
		else
		{
			return	num;
		}
	}
	return num;
}





