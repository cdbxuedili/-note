#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> 
#include<sys/ioctl.h>
#include"head.h"

int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/demo0",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}

	int value = 100;
	int x;
//	ioctl(fd,2);
	ioctl(fd,DEMO_CMD1);

//	ioctl(fd,DEMO_CMD2,value);
	ioctl(fd,DEMO_CMD2,&value);

	ioctl(fd,DEMO_CMD3,&x);
	printf("x = %d\n",x);
	close(fd);
	return 0;
}
