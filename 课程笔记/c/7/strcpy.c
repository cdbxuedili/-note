#include <stdio.h>
#include <string.h>


int main(int argc, const char *argv[])
{
	char a[15] = "hello";
	char b[15] = "world";
	puts(a);
//	strcpy(a,"world");
	strcpy(a,b);
//	strcpy("hello","world");错误!!!
	puts(a);
	return 0;
}
