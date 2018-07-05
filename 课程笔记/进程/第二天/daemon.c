#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, const char *argv[])
{
	pid_t pid;

	pid = fork();

	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if(pid == 0)
	{
		if(-1 == setsid())
		{
			printf("setsid is fail\n");
			exit(1);
		}

		if(-1 == chdir("/home/linux/"))
		{
			perror("chdir");
			exit(1);
		}

		umask(0);

		int size,i;

		size = getdtablesize();

		for(i = 0;i < size;i++)
		{
			close(i);
		}
		
		FILE *fp = fopen("/home/linux/1.txt","r+");

		while(1)
		{
			fprintf(fp,"hello world\n");
			sleep(1);
			fflush(fp);
		}

	}
	else
	{
		exit(0);//1、父进程退出
	}


	return 0;
}
