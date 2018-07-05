#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/led",O_RDWR);

	sleep(3);

	close(fd);
	return 0;
}
