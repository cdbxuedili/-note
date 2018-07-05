#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t tid1,tid2;
sem_t led1,led2;

void *fun1(void *args)
{
	while(1)
	{
		sem_wait(&led1);// p 操作 -1
	
		printf("hello ");
			
		sem_post(&led2);// v 操作 +1
		
	}
}

void *fun2(void *args)
{
	while(1)
	{
		sem_wait(&led2);

		printf("world\n");

		sem_post(&led1);
	}


}

int main(int argc, const char *argv[])
{
	if(-1 == sem_init(&led1,0,1))
	{
		perror("sem_init1");
		exit(1);
	}
	
	if(-1 == sem_init(&led2,0,0))
	{
		perror("sem_init2");
		exit(1);
	}
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
