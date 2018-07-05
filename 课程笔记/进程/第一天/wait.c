#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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
		while(1);

		exit(0);
	}
	else
	{
		if(-1 == waitpid(-1,NULL,WNOHANG))
		{
			perror("wait");
			exit(1);
		}

		exit(0);
	}
	

	return 0;
}
