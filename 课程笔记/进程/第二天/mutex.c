#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


pthread_mutex_t suo;

pthread_t tid1,tid2;

void *fun1(void *args)
{
	while(1)
	{
		pthread_mutex_lock(&suo);
		printf("hello\n");
	
		sleep(1);
		pthread_mutex_unlock(&suo);
	}
}

void *fun2(void *args)
{
	while(1)
	{
		pthread_mutex_lock(&suo);
		printf("world\n");

		sleep(1);
		pthread_mutex_unlock(&suo);
	}
}

int main(int argc, const char *argv[])
{
	
	pthread_mutex_init(&suo,NULL);

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
