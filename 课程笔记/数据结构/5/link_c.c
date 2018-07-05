#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node * next;
}link_t;

//创建
link_t * creat_link()
{
	//申请头结点的空间
	link_t * head = malloc(sizeof(link_t));
	if(head == NULL)
	{
		return NULL;
	}

	//初始化
	head->next = head;

	//返回
	return head;
}

//判空
int isnull(link_t * head)
{
	return head->next == head;
}

//打印
int print_link(link_t * head)
{
	//判空
	if(isnull(head))
	{
		return -1;
	}
	//标记头结点
	link_t * temp = head;
	
	//打印
	head = head->next;
	while(head != temp)
	{
		printf("%d ", head->data);
		head = head->next;
	}

	printf("\n");

	return 0;
}

int main(int argc, const char *argv[])
{
	link_t * link = creat_link();

	
	return 0;
}
