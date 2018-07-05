#include <stdio.h>
#include "head.h"
#include <string.h>

extern struct dev mydev;
extern struct drv mydrv;

int main(int argc, const char *argv[])
{
	if(strcmp(mydrv.name,mydev.name) == 0)
		printf("%d\n",mydrv.p(&mydev));
	return 0;
}
