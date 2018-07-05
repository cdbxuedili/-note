#include <stdio.h>
#include <string.h>


int main(int argc, const char *argv[])
{
	char a[6] = "hello";
	strcpy(&a[1],a);
	puts(a);
	return 0;
}
