#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int main(int argc, const char *argv[])
{
	
	pid_t pid;
	int status;

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
		wait(&status);

		if(WIFEXITED(status))
		{
			printf("exit\n");
		}
		else if(WIFSIGNALED(status))
		{
			printf("signal\n");
		}

		int a =WEXITSTATUS(status);

		printf("%d\n",a);

		printf("%d\n",status);

		exit(0);
	}
	

	return 0;
}
