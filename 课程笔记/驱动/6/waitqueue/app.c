#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, const char *argv[])
{
	int fd;
	
	pid_t pid;

	fd = open("/dev/demo",O_RDWR);
	
	char buf[10];
	pid = fork();
	if(pid == -1)
	{
	
	}
	else if(pid == 0)
	{
		//读	
		read(fd,buf,sizeof(buf));
		printf("user read: %s\n",buf);
	}
	else 
	{
		sleep(1);
		//写
		write(fd,"hello",6);
	}
	return 0;
}
