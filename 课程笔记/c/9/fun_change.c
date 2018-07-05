#include <stdio.h>

int fun(int m,int n);

int main(int argc, const char *argv[])
{
	int a = 10,b = 5;
	fun(a,b);
	printf("a:%d b:%d\n",a,b);
	return 0;
}

int fun(int m,int n)
{
	int temp;
	temp = m;
	m = n;
	n = temp;
	printf("m:%d n:%d\n",m,n);
	return 0;
}
