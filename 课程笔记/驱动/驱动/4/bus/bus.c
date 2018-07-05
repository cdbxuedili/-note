#include<stdio.h>
#include<string.h>
#include"head.h"

extern struct dev mydev;
extern struct drv mydrv;


int main(int argc, const char *argv[])
{
	if(strcmp(mydev.name,mydrv.name) == 0)
		printf("%d\n",mydrv.p(&mydev));
	return 0;
}
