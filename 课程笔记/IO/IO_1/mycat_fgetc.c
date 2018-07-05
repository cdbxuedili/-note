#include <stdio.h>



int main(int argc, const char *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr,"please input path of file!\n");
		return -1;
	}
	
	FILE *fp = NULL;
	int ch = 0;

	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		perror("fail to fopen");
		return -1;
	}

	while(1)
	{
		ch = fgetc(fp);
		if(ch == EOF) //要么出错进入else中的fprintf,正确读到文件末尾进入feof执行break;   
		{
			if(feof(fp))
			{
				break;
			}
			else
			{
				fprintf(stderr,"fail to fgetc\n");
				return -1;
			}
		}
		fputc(ch,stdout);
	}




	return 0;
}
