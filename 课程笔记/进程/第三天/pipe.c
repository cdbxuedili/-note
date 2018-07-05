#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, const char *argv[])
{
	pid_t pid;
	int fd[2];
	
	if(-1 == pipe(fd))
	{
		perror("pipe");
		exit(1);
	}

	pid = fork();

	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if(pid == 0)
	{
		
		close(fd[0]);
		char buf[] = "xiepeng";
		write(fd[1],buf,sizeof(buf));
		
		exit(0);
	}
	else
	{
		char buf1[128] = {0};
		wait(NULL);

		close(fd[1]);
		read(fd[0],buf1,sizeof(buf1));

		printf("%s\n",buf1);

		exit(0);
	
	}


	return 0;
}
