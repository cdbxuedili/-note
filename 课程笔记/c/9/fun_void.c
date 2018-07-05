#include <stdio.h>

void fun(void);

int main(int argc, const char *argv[])
{
	fun();
	return 0;
}

void fun(void)
{
	printf("hello world!\n");
	return ;
}

