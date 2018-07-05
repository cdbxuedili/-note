#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int main(int argc, const char *argv[])
{
	
	pid_t pid;

	signal(SIGCHLD,SIG_IGN);

	pid = fork();

	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if(pid == 0)
	{
		exit(0);
	}
	else
	{
		while(1);
		exit(0);
	}
	

	return 0;
}
