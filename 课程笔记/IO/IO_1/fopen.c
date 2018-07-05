#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	fp = fopen("./1.txt","a+");	
	if(fp == NULL)
	{
	//	fprintf(stderr,"fail to open:%s\n",strerror(errno));
		perror("fail to open");
		exit(1);
	}


	if(0 != fclose(fp))
	{
		perror("fail to close");
		exit(1);
	}

	return 0;
}
