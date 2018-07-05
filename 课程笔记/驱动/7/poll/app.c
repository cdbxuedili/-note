#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/select.h>

int main(int argc, const char *argv[])
{
	int fd;
	fd = open("/dev/demo",O_RDWR);
	
	int maxfd = fd;

	int n;
	
	fd_set readfds;
	fd_set writefds;

	char buf[10];
	while(1)
	{
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);

		FD_SET(fd,&readfds);
		FD_SET(fd,&writefds);
		n = select(maxfd + 1,&readfds,&writefds,NULL,NULL);

		if(FD_ISSET(fd,&readfds))
		{
			read(fd,buf,sizeof(buf));
			printf("usr read:%s\n",buf);
		}
			
		sleep(3);
		if(FD_ISSET(fd,&writefds))
		{
			write(fd,"hello",6);	
		}
	}
	return 0;
}
