#include <stdio.h>

void (*fun(void (*)(int),int))(int);
//void(*)(int)  fun(void (*)(int),int);
void fun1(int);


int main(int argc, const char *argv[])
{
	int num = 123;
	fun(fun1,num);
	return 0;
}


void (*fun(void (*p)(int),int n))(int)
{
	p(n);
	return p;
}

void fun1(int num)
{
	printf("num = %d\n",num);
	return ;
}



