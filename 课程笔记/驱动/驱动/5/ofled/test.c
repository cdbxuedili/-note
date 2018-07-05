#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> 
#include<sys/ioctl.h>
#include"led.h"

int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/demo0",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}

	while(1)
	{
		ioctl(fd,LED2_ON);
		sleep(1);
		ioctl(fd,LED1_ON);
		sleep(1);
		ioctl(fd,LED3_ON);
		sleep(1);
		ioctl(fd,LED4_ON);
		sleep(1);

		ioctl(fd,LED2_OFF);
		sleep(1);
		ioctl(fd,LED1_OFF);
		sleep(1);
		ioctl(fd,LED3_OFF);
		sleep(1);
		ioctl(fd,LED4_OFF);
		sleep(1);
		
	}

	return 0;
}
