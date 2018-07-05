#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	
	pid_t pid;

	pid = fork();

	if(pid < 0) 
	{
		exit(1);
	}
	else if(pid == 0)
	{
	//	char *buf[] = {"./hello",NULL};
		char *env[] = {"PATH=123","ABC=456"};
		//execl("/home/linux/xie/classnote/18031/process/1/hello","./hello",NULL);
		//execv("/home/linux/xie/classnote/18031/process/1/hello",buf);
		execle("/usr/bin/env","/usr/bin/env",NULL,env);
		printf("hello\n");
		exit(0);
	}
	else
	{
		printf("hello world\n");
		exit(0);
	}


	return 0;
}
