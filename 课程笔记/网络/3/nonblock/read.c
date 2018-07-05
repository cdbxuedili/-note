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
		//	fd = open("./myfifo",O_RDONLY | O_NONBLOCK);
			fd = open("./myfifo",O_RDONLY);
		}
		else//其他错误
		{
		
		}
	}
	else //有名管道不存在，当前任务创建
	{
	//	fd = open("./myfifo",O_RDONLY | O_NONBLOCK);	
		fd = open("./myfifo",O_RDONLY);	
	}

	char buf[10];
	char buff[10];
	ssize_t n;
	
	int flag;
	flag = fcntl(fd,F_GETFL);//flag此时存放O_RDONLY
	flag |= O_NONBLOCK;//此时只是flag具备O_NONBLOCK属性
	fcntl(fd,F_SETFL,flag);//fd具备O_NONBLOCK属性

	flag = fcntl(0,F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(0,F_SETFL,flag);

	while(1)
	{
		memset(buf,0,sizeof(buf));
		n = read(fd,buf,sizeof(buf));
		printf("n = %d,buf = %s\n",n,buf);
//		sleep(1);
		read(0,buff,sizeof(buff));
		printf("stdin:%s\n",buff);
	}
	return 0;
}
