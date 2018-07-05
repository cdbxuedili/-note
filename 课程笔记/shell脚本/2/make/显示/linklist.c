
#include "head.h"

LINKLIST *create_empty_linklist()
{
	LINKLIST *head;

	head = (LINKLIST *)malloc(sizeof(LINKLIST));
	head->next = NULL;

	return head;
}

int insert_head_linklist(LINKLIST *L,DATATYPE data)
{
	struct node *temp;
	struct node *head = L;
	
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = data;
	
	temp->next = head->next;
	head->next = temp;

	return 0;
}

int insert_tail_linklist(LINKLIST *L,DATATYPE data)
{
	struct node *p = L;
	struct node *temp;
	
	//遍历到链表的尾部,while结束时，p指向最后一个结点
	while(p->next != NULL) p = p->next;

	//分配结点，填值
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = data;

	//尾部插入
	p->next = temp;
	temp->next = NULL;

	return 0;
}

int delete_assign_linklist(LINKLIST *L,DATATYPE data)
{
	struct node * p = L;
	struct node *temp;

	if(p->next == NULL)
	{
		printf("The linklist is empty.\n");
		return -1;
	}
	
	//当while结束的时候，p指向要删除结点的前一结点
	while(p->next && p->next->data != data) p = p->next;
	
	if(p->next == NULL)
	{
		printf("The data is not exist.\n");
		return -1;
	}

	//删除
	temp = p->next;
	p->next = p->next->next;
	free(temp);
	temp = NULL;
	
	return 0;
}

int print_linklist(LINKLIST *L)
{
	struct node *p;
	
	p = L->next;

	while(p)
	{
		printf("%d ",p->data);
		p = p->next;
	}

	printf("\n");

	return 0;
}


