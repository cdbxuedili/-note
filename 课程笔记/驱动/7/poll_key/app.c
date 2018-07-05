#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/key",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	
	int key;
	int maxfd = fd;
	fd_set readfds;
	struct timeval t;
	int ret;
	while(1)
	{	
		t.tv_sec = 5;
		t.tv_usec = 0;
		FD_ZERO(&readfds);
		FD_SET(fd,&readfds);
		ret = select(maxfd + 1,&readfds,NULL,NULL,&t);
		printf("ret = %d\n",ret);

		if(FD_ISSET(fd,&readfds))
		{
			read(fd,&key,sizeof(key));
			printf("key = %d\n",key);
		}
	}

	return 0;
}
