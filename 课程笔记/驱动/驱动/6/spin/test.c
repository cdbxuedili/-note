#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/demo",O_RDWR);

	if(fd == -1)
	{
		perror("open");
		return -1;
	}

	sleep(10);
	close(fd);
	return 0;
}
