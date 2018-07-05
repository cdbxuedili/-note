#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
	char buf[128] = {0};

	if(-1 == mkfifo("./fifo",0666))
	{
		if(errno != EEXIST)
		{
			perror("mkfifo");
			exit(1);
		}
		
	}

	int fd = open("./fifo",O_WRONLY);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}

	while(1)
	{
		bzero(buf,sizeof(buf));

		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf) - 1] = '\0';

		write(fd,buf,sizeof(buf));

	}


	return 0;
}
