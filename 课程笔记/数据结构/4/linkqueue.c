#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;//存数据
	struct node * next;//保存下一个结点的地址
}node_t;//结点的数据类型

typedef struct queue
{
	node_t * head;//头指针
	node_t * tail;//尾指针
}queue_t;//队列的数据类型


//创建
queue_t * creat_queue()
{
	//申请头结点的数据类型
	node_t * head = malloc(sizeof(node_t));
	if(head == NULL)
	{
		return NULL;
	}

	//初始化
	head->next = NULL;

	//申请头指针和尾指针的存储空间
	queue_t * queue = malloc(sizeof(queue_t));
	if(queue == NULL)
	{
		return NULL;
	}

	//初始化头指针尾指针的指向
	queue->head = head;
	queue->tail = head;

	return queue;//返回标识
}

//判空
int isnull(queue_t * queue)
{
	return queue->head->next == NULL;
//	return queue->head == queue->tail;
}


//入队
int in_queue(queue_t * queue, int data)
{
	//申请新结点的存储空间
	node_t * newnode = malloc(sizeof(node_t));

	//存入数据
	newnode->data = data;

	//入队
	newnode->next = queue->tail->next;
	queue->tail->next = newnode;

	//修改尾指针tail的指向
	queue->tail = newnode;

	return 0;
}

//出队
int out_queue(queue_t * queue, int * data)
{
	//判断实施条件
	if(isnull(queue))
	{
		return -1;
	}

	//备份出队的数据
	node_t * temp = queue->head->next;

	//出队数据
	queue->head->next = temp->next;

	//获取出队数据
	*data = temp->data;

	//释放出队数据
	free(temp);

	//如果出队数据后，队列为空，要找回尾指针的指向
	if(queue->head->next == NULL)
	{
		queue->tail = queue->head;
	}

	return 0;
}

//获取队列的长度
int get_length(queue_t * queue)
{
	//判断实施条件
	if(isnull(queue))
	{
		return 0;
	}

	int len = 0;
	node_t * head = queue->head;
	head = head->next;
	while(head != NULL)
	{
		len++;
		head = head->next;
	}

	return len;
}

//打印数据
int  print_queue(queue_t * queue)
{
	//判空
	if(isnull(queue))
	{
		return -1;
	}

	node_t * head = queue->head;
	head = head->next;
	printf("队头：");
	while(head != NULL)
	{
		printf("%d ", head->data);
		head = head->next;
	}
	printf("队尾\n");

	return 0;
}

//清空
int clean_queue(queue_t * queue)
{
	int temp;
	while(!isnull(queue))
	{
		out_queue(queue, &temp);
	}
	return 0;
}

//销毁
int dis_queue(queue_t * queue)
{
	//清空
	clean_queue(queue);
	//释放
	free(queue->head);
	free(queue);

	return 0;
}

//逆向打印
int reprint_queue(queue_t * queue)
{
	//创建临时栈
	int * stack1 = malloc(sizeof(int) * get_length(queue));
	int top1 = -1;

	int * stack2 = malloc(sizeof(int) * get_length(queue));
	int top2 = -1;
	
	int data;
	//当队列不为空，出队数据，进栈1
	while(!isnull(queue))
	{
		out_queue(queue, &data);
		stack1[++top1] = data;
	}

	//当栈1不为空，出栈1，出来一个打印一个，进栈2
	while(top1 != -1)
	{
		data =	stack1[top1--];
		printf("%d ", data);
		stack2[++top2] = data;
	}
	printf("\n");

	//当栈2不为空，出栈2，进队列
	while(top2 != -1)
	{
		data = stack2[top2--];
		in_queue(queue, data);
	}

	//释放
	free(stack1);
	free(stack2);

	return 0;
}

int main(int argc, const char *argv[])
{
	queue_t * queue = creat_queue();
	if(queue == NULL)
	{
		return -1;
	}

	int i;
	for(i = 1; i <= 10; i++)
	{
		in_queue(queue, i * 10);
	}
	print_queue(queue);

	int out_data;
	for(i = 1; i <= 3; i++)
	{
		out_queue(queue, &out_data);
		printf("out_data:%d\n", out_data);
		print_queue(queue);
	}

	reprint_queue(queue);

	int ret = get_length(queue);
	printf("length:%d\n", ret);

	clean_queue(queue);

	dis_queue(queue);

	return 0;
}
