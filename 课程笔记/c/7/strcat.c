#include <stdio.h>
#include <string.h>


int main(int argc, const char *argv[])
{
	char a[128] = "hello";
	char b[] = "world";
	//strcat(a,"world");
	strcat(a,b);
	puts(a);
	return 0;
}
