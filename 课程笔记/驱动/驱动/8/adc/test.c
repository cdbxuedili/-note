#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, const char *argv[])
{
	int fd;
	int data;
	fd = open("/dev/myadc",O_RDWR);

	while(1)
	{
		read(fd,&data,sizeof(data));
		printf("%d\n",data);
		sleep(1);
	}
	return 0;
}
