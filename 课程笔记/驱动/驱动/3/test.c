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

	write(fd,"farsight",8);

	ssize_t n;
	char buf[20];
	n = read(fd,buf,20);
	printf("n = %d\n",n);
	printf("recv data from kernel:%s\n",buf);
	return 0;
}
