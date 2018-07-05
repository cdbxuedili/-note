#include <stdio.h>

char * fun();

int main(int argc, const char *argv[])
{
	char *str = NULL;
	str = fun();
	printf("%s\n",str);
	return 0;
}


char *fun()
{
	char buf[] = "hello world";
	return buf;
}
