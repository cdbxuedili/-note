#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

pthread_t tid1,tid2,tid3;
sem_t led1,led2,led3;


void *fun1(void *args)
{
	int i = 0;
	for(i = 0;i < 10;i++)
	{
		sem_wait(&led1);
	
		printf("fun1 : %ld\n",tid1);
	
		sem_post(&led2);
	}
	pthread_exit(NULL);
}

void *fun2(void *args)
{
	int i;
	for(i = 0;i < 10; i++)
	{
		sem_wait(&led2);
		printf("fun2 : %ld\n",tid2);
	
		sem_post(&led3);
	}
	pthread_exit(NULL);
}

void *fun3(void *args)
{
	int i;
	for(i = 0;i < 10;i++)
	{
		sem_wait(&led3);

		printf("fun3 : %ld\n",tid3);

		sem_post(&led1);
	}
	pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
	sem_init(&led1,0,1);
	sem_init(&led2,0,0);
	sem_init(&led3,0,0);


	pthread_create(&tid1,NULL,fun1,NULL);
	pthread_create(&tid2,NULL,fun2,NULL);
	pthread_create(&tid3,NULL,fun3,NULL);


	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);

	return 0;
}
