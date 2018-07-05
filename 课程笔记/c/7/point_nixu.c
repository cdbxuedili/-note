#include <stdio.h>
#include <string.h>


int main(int argc, const char *argv[])
{
	char a[128];
	char temp = 0;
	gets(a);
	char *p = &a[0];
	char *q = &a[0] + strlen(a) - 1;

	while(p < q)
	{
		temp = *p;
		*p = *q;
		*q = temp;
		p++;
		q--;
	}
	puts(a);
	return 0;
}
