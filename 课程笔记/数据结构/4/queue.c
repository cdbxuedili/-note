#include <stdio.h>
#include <stdlib.h>
typedef struct queue
{
	int *data;//存数据
	int size;//标记数据元素个数
	int head;//即将要取数据的位置
	int tail;//即将要存数据的位置
}queue_t;//顺序循环队列的类型

//创建
queue_t * creat_queue(int size)
{
	queue_t * queue = malloc(sizeof(queue_t));
	if(queue == NULL)
	{
		return NULL;
	}

	//初始化
	queue->data = malloc(sizeof(int) * size);
	if(queue->data == NULL)
	{
		return NULL;
	}

	queue->size = size;

	queue->head = 0;
	queue->tail = 0;

	return queue;
}
//判满
int isfull(queue_t * queue)
{
	return  (queue->tail + 1) % queue->size == queue->head ;
}
//判空
int isnull(queue_t * queue)
{
	return queue->head == queue->tail;
}

//入队(尾入)
int in_queue(queue_t * queue, int data)
{
	//判断实施条件
	if(isfull(queue))
	{
		return -1;
	}

	//数据入队
	queue->data[queue->tail] = data;

	//修改tail的值
	queue->tail = (queue->tail+1) % queue->size;
	
	return 0;
}

//出队（头出）
int out_queue(queue_t * queue, int * data)
{
	//判空
	if(isnull(queue))
	{
		return -1;
	}

	//获取出队数据
	*data = queue->data[queue->head];

	//修改head的位置
	queue->head = (queue->head + 1) % queue->size ;

	return 0;
}

//打印数据
int print_queue(queue_t * queue)
{
	//判空
	if(isnull(queue))
	{
		return -1;
	}
	//打印数据
	int i;
	printf("队头：");
	for(i = queue->head; i != queue->tail; i = (i+1)%queue->size)
	{
		printf("%d ", queue->data[i]);
	}
	printf("队尾\n");
	
	return 0;
}

//获取队列长度
int get_length(queue_t * queue)
{
	return (queue->tail + queue->size - queue->head) % queue->size;
}

//清空
int clean_queue(queue_t * queue)
{
	queue->head = 0;
	queue->tail = 0;

	return 0;
}
//销毁
int dis_queue(queue_t * queue)
{
	free(queue->data);
	free(queue);

	return 0;
}
int main(int argc, const char *argv[])
{
	queue_t * queue = creat_queue(10);
	if(queue == NULL)
	{
		return -1;
	}
	
	int i;
	for(i = 1; i <= 9; i++)
	{
		in_queue(queue, i * 10);
	}
	print_queue(queue);

	int out_data;
	for(i = 1; i <= 3; i++)
	{
		out_queue(queue,&out_data );
		printf("out_data:%d\n", out_data);
		print_queue(queue);
	}

	int len = get_length(queue);
	printf("len:%d\n", len);

	clean_queue(queue);

	dis_queue(queue);

	return 0;
}
