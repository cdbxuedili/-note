#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> 

int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/abcde",O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	return 0;
}
