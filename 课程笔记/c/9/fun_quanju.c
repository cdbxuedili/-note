#include <stdio.h>


int num = 1234;

int fun()
{
	num = 234;
	return 0;
}

int main(int argc, const char *argv[])
{
	printf("num:%d\n",num);
	fun();
	printf("num:%d\n",num);
	return 0;
}
