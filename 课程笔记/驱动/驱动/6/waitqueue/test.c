#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, const char *argv[])
{
	int fd;
	char buf[10];
	fd = open("/dev/demo",O_RDWR);

	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	pid_t pid;

	pid = fork();

	if(pid == -1)
	{

	}
	else if(pid == 0)//子进程
	{
		sleep(10);
		printf("*********write1**********\n");
		write(fd,"hello",5);
		printf("*********write2**********\n");
	}
	else if(pid > 0) //父进程
	{
		printf("*********read1**********\n");
		read(fd,buf,sizeof(buf));
		printf("%s\n",buf);
		printf("*********read2**********\n");
		
	}

	close(fd);
	return 0;
}
