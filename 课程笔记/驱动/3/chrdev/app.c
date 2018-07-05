#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/demo",O_RDWR);
	
	ssize_t n;
	char buf[64];
	n = read(fd,buf,sizeof(buf));	
	printf("n = %d,buf = %s\n",n, buf);

	write(fd,"I am from user",15);
	return 0;
}
