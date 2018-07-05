#include <stdio.h>
#include <strings.h>


int main(int argc, const char *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr,"please input path of file!\n");
		return -1;
	}
	
	FILE *fp = NULL;
	char buf[128]; 


	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		perror("fail to fopen");
		return -1;
	}

	while(1)
	{
		bzero(buf,sizeof(buf));
	//	memset(buf,0,sizeof(buf));
		
		if(NULL == fgets(buf,sizeof(buf),fp))
		{
			if(feof(fp))
				break;
			else
			{
				fprintf(stderr,"fail to fgets\n");
				return -1;
			}
		}
		fputs(buf,stdout);
	}




	return 0;
}
