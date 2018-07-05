#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>

int fd;
int key;
void func(int signo)
{
	if(signo == SIGIO)
	{
		read(fd,&key,sizeof(key));
		printf("key = %d\n",key);
	}
}

int main(int argc, const char *argv[])
{
	
	signal(SIGIO,func);

	fd = open("/dev/key",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	

	int flag;

	flag = fcntl(fd,F_GETFL);
	flag |= FASYNC;
	fcntl(fd,F_SETFL,flag);
	fcntl(fd,F_SETOWN,getpid());

	while(1)
	{
		printf("hello\n");
		sleep(1);
	}
	return 0;
}
