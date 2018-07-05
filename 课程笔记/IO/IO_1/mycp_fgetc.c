#include <stdio.h>



int main(int argc, const char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr,"please input path of file!\n");
		return -1;
	}
	
	FILE *fp = NULL;
	FILE *fp1 = NULL;
	int ch = 0;

	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		perror("fail to open argv[1]");
		return -1;
	}

	fp1 = fopen(argv[2],"w");
	if(fp1 == NULL)
	{
		perror("fail to open argv[2]");
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
		fputc(ch,fp1);
	}


	fclose(fp);
	fclose(fp1);

	return 0;
}
