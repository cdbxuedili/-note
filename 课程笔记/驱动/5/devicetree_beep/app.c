#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "head.h"

int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/beep",O_RDWR);

	ioctl(fd,BEEP_ON);	
	sleep(3);
	ioctl(fd,BEEP_OFF);	
	return 0;
}
