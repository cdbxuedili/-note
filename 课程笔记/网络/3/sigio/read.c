#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<signal.h>

int fd;
char buf[10];
void func(int signo)
{
	if(signo == SIGIO)
	{
		read(fd,buf,sizeof(buf));	
		printf("buf = %s\n",buf);
	}
}

int main(int argc, const char *argv[])
{
	signal(SIGIO,func);//告诉内核当前进程要捕捉SIGIO信号
	if(mkfifo("./myfifo",0664) == -1)
	{
		if(errno == EEXIST)//有名管道已经存在
		{
			fd = open("./myfifo",O_RDONLY);
		}
		else//其他错误
		{
		
		}
	}
	else //有名管道不存在，当前任务创建
	{
		fd = open("./myfifo",O_RDONLY);	
	}

	char buf[10];
	char buff[10];
	ssize_t n;
	
	int flag;
	flag = fcntl(fd,F_GETFL);
	flag |= O_ASYNC;
	fcntl(fd,F_SETFL,flag);
	fcntl(fd,F_SETOWN,getpid());

	while(1)
	{
		printf("hello world!\n");
		sleep(1);
	}
	return 0;
}
