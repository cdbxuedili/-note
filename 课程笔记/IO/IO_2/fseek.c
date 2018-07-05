#include <stdio.h>



int main(int argc, const char *argv[])
{
	FILE *fp;
	int ret;
	fp = fopen("./1.txt","r+");
	if(fp == NULL)
	{
		perror("fail to fopen");
		return -1;
	}

	ret = fseek(fp,-17,SEEK_END);
	if(ret == -1)
	{
		perror("fail to fseek");
		return -1;
	}

	printf("size:%ld\n",ftell(fp));


	fseek(fp,0,SEEK_END);
	printf("size:%ld\n",ftell(fp));

	rewind(fp);
	printf("size:%ld\n",ftell(fp));

	return 0;
}
