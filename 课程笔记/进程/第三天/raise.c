#include <stdio.h>
#include <signal.h>
#include <sys/types.h>


int main(int argc, const char *argv[])
{

	sleep(3);

	raise(SIGQUIT);

	sleep(3);

	return 0;
}
