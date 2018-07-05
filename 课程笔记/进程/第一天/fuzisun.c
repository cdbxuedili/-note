#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, const char *argv[])
{
	pid_t pid;

	pid = fork();

	if(pid < 0)
	{
		perror("fork1");
		exit(1);
	}
	else if(pid == 0)
	{
		pid_t pid1;

		pid1 = fork();

		if(pid1 < 0)
		{
			perror("fork2");
			exit(1);
		}
		else if(pid1 == 0)
		{
			sleep(1);
			printf("grandson's id is %d\n",getpid());
			printf("son's id is %d\n",getppid());

			exit(0);
		}
		else
		{
			exit(0);
		}

	}
	else
	{
		wait(NULL);
		while(1);
		exit(0);
	}



	return 0;
}
