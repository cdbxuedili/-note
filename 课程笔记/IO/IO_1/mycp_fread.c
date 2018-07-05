#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, const char *argv[])
{
	int ret_fread;
	if(argc != 3)
	{
		fprintf(stderr,"please input path of file!\n");
		exit(1);
	}

	FILE* fp1 = NULL;
	FILE* fp2 = NULL;

	fp1 = fopen(argv[1],"r");
	if(fp1 == NULL)
	{
		perror("fail to fopen argv[1]");
		exit(1);
	}

	fp2 = fopen(argv[2],"w");
	if(fp2 == NULL)
	{
		perror("fail to fopen argv[2]");
		exit(1);
	}

	char buf[128];
	
	while(1)
	{
		bzero(buf,sizeof(buf));

		ret_fread = fread(buf,sizeof(char),sizeof(buf)/sizeof(char),fp1);
		if(ret_fread < 0)
		{
			fprintf(stderr,"fail to fread\n");
			exit(1);
		}
		else if(ret_fread == 0)
		{
			break;
		}
		else
		{
			fwrite(buf,sizeof(char),ret_fread,fp2);
		}
	}

	fclose(fp1);
	fclose(fp2);




	return 0;
}
