#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/select.h>

int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/demo0",O_RDWR);

	int maxfd;
	maxfd = fd + 1;

	fd_set readfds;
	fd_set writefds;
	
	int n;
	char buf[10];
	while(1)
	{
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_SET(fd,&readfds);
		FD_SET(fd,&writefds);

		n = select(maxfd,&readfds,&writefds,NULL,NULL);

		if(FD_ISSET(fd,&readfds))
		{
			printf("**********read1**************\n");
			read(fd,buf,sizeof(buf));
			printf("%s\n",buf);
			printf("**********read2**************\n");
		}
		if(FD_ISSET(fd,&writefds))
		{
			printf("**********write1**************\n");
			write(fd,"hello",5);
			printf("**********write2**************\n");
		}
		sleep(1);
	}
	return 0;
}
