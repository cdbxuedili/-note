#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc, const char *argv[])
{
	int fd;
	int len;
	fd = open("./time.c",O_RDONLY);
	if(fd < 0)
	{
		perror("fail to open");
		return -1;
	}

	len = lseek(fd,0,SEEK_END);
	if(len < 0)
	{
		perror("fail to lseek");
		return -1;
	}
	printf("len:%d\n",len);
	close(fd);
	return 0;
}
