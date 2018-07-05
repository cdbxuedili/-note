#include <stdio.h>

void fun()
{
 	static int a = 0;
	a = a+1;
	printf("%d\n",a);
	return;
}


int main(int argc, const char *argv[])
{
	fun();
	fun();
	fun();
	return 0;
}
