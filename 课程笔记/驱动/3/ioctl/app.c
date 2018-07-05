#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/ioctl.h>
#include "head.h"


int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/demo",O_RDWR);
	
//	ioctl(fd,1);//
//	ioctl(fd,2);//如果命令传递的是２则不能和驱动中的ioctl进行匹配
				//现在的这种用法是错误的

	int value = 100;
	struct test t;

	ioctl(fd,TEST_CMD1);
	ioctl(fd,TEST_CMD2);
	ioctl(fd,TEST_CMD3,value);
	ioctl(fd,TEST_CMD4,&value); //传惨过程中实现了强转,(unsigned long)&value

	ioctl(fd,TEST_CMD5,&t);
	printf("%d,%c\n",t.a,t.b);
	return 0;
}
