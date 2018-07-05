#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i = 1;
#if 0
	while(i > 100)
	{
		i++;
	}
#endif
#if 1
	do
	{
		i++;
	}while(i > 100);
#endif
	printf("%d\n",i);
	return 0;
}
