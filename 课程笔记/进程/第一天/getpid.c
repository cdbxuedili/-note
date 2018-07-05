#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	pid_t pid,ppid;

	pid = getpid();
	
	printf("%d\n",pid);

	ppid = getppid();
	printf("%d\n",ppid);


	while(1);


	return 0;
}
