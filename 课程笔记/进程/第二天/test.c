#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a = 0,b = 0,i = 0;
pthread_t tid1,tid2;

void *fun1(void *args)
{
	while(1)
	{
		i++;
		a = i;
		b = i;
	}
}

void *fun2(void *args)
{
	while(1)
	{
		if(a != b)
		{
			printf("a = %d b = %d i = %d\n",a,b,i);
		}
	}

}

int main(int argc, const char *argv[])
{
	
	if(0 != pthread_create(&tid1,NULL,fun1,NULL))
	{
		printf("pthread_create is fail\n");
		exit(1);
	}


	if(0 != pthread_create(&tid2,NULL,fun2,NULL))
	{
		printf("pthread_create is fail\n");
		exit(1);
	}

	if(0 != pthread_join(tid1,NULL))
	{
		printf("pthread_join is fail\n");
		exit(1);
	}

	if(0 != pthread_join(tid2,NULL))
	{
		printf("pthread_join is fail\n");
		exit(1);
	}
	return 0;
}
