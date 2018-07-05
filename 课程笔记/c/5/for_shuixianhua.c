#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i;
	int x = 0,y = 0,z = 0;
	for(i = 100;i < 1000;i++)
	{
		x = i/100;
		y = i/10%10;
		z = i%10;
		if(x*x*x+y*y*y+z*z*z == i)
		{
			printf("%d\n",i);
		}
	}
	return 0;
}
