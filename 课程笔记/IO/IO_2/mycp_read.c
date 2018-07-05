#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <fcntl.h>


int main(int argc, const char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr,"please input path of file!\n");
		return -1;
	}

	int fd1;
	int fd2;
	char buf[128];
	int ret_read;
	//open
	fd1 = open(argv[1],O_RDONLY);
	if(fd1 < 0)
	{
		perror("fail to open argv[1]");
		return -1;
	}

	fd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0666);
	if(fd2 < 0)
	{
		perror("fail to open argv[2]");
		return -1;
	}

	while(1)
	{
		bzero(buf,sizeof(buf));
		//memset(buf,0,sizeof(buf));
		ret_read = read(fd1,buf,sizeof(buf));
		if(ret_read < 0)
		{
			perror("fail to read");
			return -1;
		}
		else if(ret_read == 0)
		{
			break;
		}
		else
		{
			write(fd2,buf,ret_read);
		}
	}

	close(fd1);
	close(fd2);
	return 0;
}
