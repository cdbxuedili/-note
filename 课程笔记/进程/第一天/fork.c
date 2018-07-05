#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	pid_t pid;

	pid = fork();

	if(pid < 0)
	{
		perror("fork");
		return -1;
	}
	else if(0 == pid)
	{
		printf("I'm child\n");
		printf("child's id is %d\n",getpid());
		printf("child's father's id is %d\n",getppid());
		
	}
	else
	{
		sleep(1);
		printf("I'm father\n");
		printf("father's id is %d\n",getpid());
		printf("father's father's id is %d\n",getppid());
		
	}

	return 0;
}
