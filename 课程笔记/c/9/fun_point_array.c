#include <stdio.h>

int add(int m,int n);
int del(int m,int n);
int mul(int m,int n);

int main(int argc, const char *argv[])
{
	int a = 10,b = 5;
	int (*c[3])(int,int) = {add,del,mul};
	//	int (*)(int ,int)c[3] = {add,del,mul};	
	//int (int,int)  ---> int (*p)(int,int) ---->int(*)(int,int) 
	printf("%d\n",c[0](a,b));
	printf("%d\n",c[1](a,b));
	printf("%d\n",c[2](a,b));

	return 0;
}


int add(int m,int n)
{
	return m+n;
}

int del(int m,int n)
{
	return m-n;
}

int mul(int m,int n)
{
	return m*n;
}
