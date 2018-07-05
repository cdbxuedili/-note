#include <stdio.h>



int main(int argc, const char *argv[])
{
	FILE* fp = NULL;
	fp = fopen("./111.c","r");
	if(fp == NULL)
	{
		perror("fail to open");
	}
	return 0;
}
