#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<linux/input.h>

int main(int argc, const char *argv[])
{
	int fd;

	struct input_event ev;
	fd = open("/dev/input/event1",O_RDWR);

	while(1)
	{
		printf("start\n");
		read(fd,&ev,sizeof(ev));
		if(ev.type == EV_KEY)
			printf("code:%d,value:%d\n",ev.code,ev.value);
	}
	return 0;
}
