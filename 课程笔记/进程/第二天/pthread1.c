#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


pthread_t tid1,tid2,tid3;

void *fun1(void *args)
{
		printf("%s\n",(char *)args);
		printf("hello\n");
	//	sleep(1);
		sleep(5);

	//pthread_exit(NULL);
//	pthread_exit("xiepeng");
}

void *fun2(void *args)
{
	
	printf("world\n");
		//sleep(1);

}

void *fun3(void *args)
{
	sleep(1);
	pthread_cancel(tid1);
}

int main(int argc, const char *argv[])
{

	char *str = "xieyuxing";
	char *rv = NULL;

	if(0 != pthread_create(&tid1,NULL,fun1,str))
	{
		printf("pthread_create is fail\n");
		exit(1);
	}


	if(0 != pthread_create(&tid2,NULL,fun2,NULL))
	{
		printf("pthread_create is fail\n");
		exit(1);
	}

	if(0 != pthread_create(&tid3,NULL,fun3,NULL))
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
	if(0 != pthread_join(tid3,NULL))
	{
		printf("pthread_join is fail\n");
		exit(1);
	}

	//printf("%s\n",rv);
	return 0;
}
