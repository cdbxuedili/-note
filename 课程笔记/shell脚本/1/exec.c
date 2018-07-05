#include<stdio.h>
#include<unistd.h>
int main(int argc, const char *argv[])
{
	execl("./test.sh","test.sh",NULL);
	return 0;
}
