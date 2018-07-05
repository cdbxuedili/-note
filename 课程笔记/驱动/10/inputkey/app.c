#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<linux/input.h>


struct input_event key;
int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/input/event1",O_RDWR);
	
	
	while(1)
	{
		read(fd,&key,sizeof(key));
		if(key.type == EV_KEY)
			printf("type:%d,code:%d,value:%d\n",key.type,key.code,key.value);
	}
	return 0;
}
