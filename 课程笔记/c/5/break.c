#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i = 1;
	while(i <= 50)
	{
		i++;
		if(i == 20)
		{
			break;
		}
		printf("%d\n",i);
	}
	return 0;
}
