#include <stdio.h>
#include <signal.h>

void fun(int signum)
{

}

int main(int argc, const char *argv[])
{
	signal(SIGINT,fun);

	pause();

	printf("hello\n");

	return 0;
}
