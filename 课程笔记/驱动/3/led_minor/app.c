#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "head.h"

int main(int argc, const char *argv[])
{
	int fd[4];

	int i;
	char name[100];
	for(i = 0;i < 4;i ++)
	{
		sprintf(name,"/dev/led%d",i);
		fd[i] = open(name,O_RDWR);
	}

	while(1)
	{
		ioctl(fd[1],LED_ON);
		sleep(1);

		ioctl(fd[1],LED_OFF);
		sleep(1);
	}
	return 0;
}
