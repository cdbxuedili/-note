#include <stdio.h>

int a = 20;


int main(int argc, const char *argv[])
{
//	int a = 10;
	printf("a1:%d\n",a);
	{
//		int a = 5;
		printf("a2:%d\n",a);
		{
//			int a = 15;
			printf("a3:%d\n",a);
		}
	}
	return 0;
}
