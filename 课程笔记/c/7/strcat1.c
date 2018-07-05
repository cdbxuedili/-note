#include <stdio.h>
#include <string.h>


int main(int argc, const char *argv[])
{
	char a[128] = "hello";
	char b[] = "world";
	char c[256] = "aaaaaaa";
//	strcat(a,b);
//	strcat(c,a);
	strcat(c,strcat(a,b));
	puts(c);
	return 0;
}
