#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	alarm(0);

	pause();

	return 0;
}
