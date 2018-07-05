#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc, const char *argv[])
{
	int fd;
	if(mkfifo("./myfifo",0664) == -1)
	{
		if(errno == EEXIST)//有名管道已经存在
		{
			fd = open("./myfifo",O_WRONLY);
		}
		else//其他错误
		{
		
		}
	}
	else //有名管道不存在，当前任务创建
	{
		fd = open("./myfifo",O_WRONLY);	
	}

	char buf[10];

	while(1)
	{
		fgets(buf,sizeof(buf),stdin);
		write(fd,buf,strlen(buf) + 1);
	}
	return 0;
}
