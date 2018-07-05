#include <stdio.h>
#include <strings.h>


int main(int argc, const char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr,"please input path of file!\n");
		return -1;
	}
	
	FILE *fp = NULL;
	FILE *fp1 = NULL;
	char buf[128];

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
		bzero(buf,sizeof(buf));

		if(NULL == fgets(buf,sizeof(buf),fp))
		{
			if(feof(fp))
			{
				break;
			}
			else
			{	
				fprintf(stderr,"fail to fgets");
				return -1;
			}
		}
	
		fputs(buf,fp1);

	}


	fclose(fp);
	fclose(fp1);

	return 0;
}
