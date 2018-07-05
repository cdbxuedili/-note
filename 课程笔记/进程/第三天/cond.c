#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


pthread_cond_t tiaojian1,tiaojian2;
pthread_mutex_t suo;
pthread_t tid1,tid2,tid3;

void *fun1(void *args)
{
	while(1)
	{
		pthread_mutex_lock(&suo);

		pthread_cond_wait(&tiaojian1,&suo);

		printf("hello\n");

		pthread_mutex_unlock(&suo);
	}
}

void *fun2(void *args)
{
	while(1)
	{
		pthread_mutex_lock(&suo);
		pthread_cond_wait(&tiaojian2,&suo);

		printf("world\n");

		pthread_mutex_unlock(&suo);
	}
}


void *fun3(void *args)
{
	int a;
	while(1)
	{
		scanf("%d",&a);
		if(a == 0)
		{
			pthread_cond_signal(&tiaojian1);
		}
		else if(a == 1)
		{
			pthread_cond_signal(&tiaojian2);
		}
	}
}


int main(int argc, const char *argv[])
{
	pthread_cond_init(&tiaojian1,NULL);
	pthread_cond_init(&tiaojian2,NULL);

	pthread_mutex_init(&suo,NULL);
	
	pthread_create(&tid1,NULL,fun1,NULL);
	pthread_create(&tid2,NULL,fun2,NULL);
	pthread_create(&tid3,NULL,fun3,NULL);


	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);

	
	return 0;
}
