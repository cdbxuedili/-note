#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc, const char *argv[])
{
	int fd;
	fd = open("./123.txt",O_CREAT | O_WRONLY | O_TRUNC,0666);
	if(fd < 0)
	{
		perror("fail to open");
		return -1;
	}

	close(fd);


	return 0;
}
