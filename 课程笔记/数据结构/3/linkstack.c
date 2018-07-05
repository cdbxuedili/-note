#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
	int data ; 
	struct node *next ; 
}linkstack_t ;  

//创建 
linkstack_t *creat_stack(void)
{
	linkstack_t *head = malloc(sizeof(linkstack_t));

	if(head == NULL)
		return NULL ;
	head->next = NULL ; 

	return head ; 
}

//进栈 
int pust_stack(linkstack_t *linkstack , int data)
{
	linkstack_t *newnode = malloc(sizeof(linkstack_t));

	newnode->data = data ; 

	newnode->next = linkstack->next ; 
	linkstack->next = newnode ; 

	return 0 ; 
}

//判空 
int isnull(linkstack_t *linkstack)
{
	return linkstack->next == NULL ; 
}

//出栈 
int pop_stack(linkstack_t *linkstack, int *data)
{
	if(isnull(linkstack))
	{
		printf("栈为空, 出栈失败\n");
		return -1 ;
	}

	linkstack_t *temp = linkstack->next;

	linkstack->next = temp->next ; 

	*data = temp->data ; 

	free(temp);

	return 0 ; 
}

//获取栈顶数据 
int get_top_stack(linkstack_t *linkstack, int *data)
{
	if(isnull(linkstack))
		return -1 ; 

	*data = linkstack->next->data ; 

	return 0 ; 
}
//打印数据 
int print_stack(linkstack_t *linkstack)
{
	if(isnull(linkstack))
	{
		printf("栈为空\n");
		return -1 ; 
	}
	
	printf(">>栈顶<<\n");
	while(linkstack->next != NULL)
	{
		linkstack = linkstack->next ;
		printf("%d\n", linkstack->data);
	}
	printf(">>栈底<<\n");
	return 0 ; 
}

//清空栈 
int clean_stack(linkstack_t *linkstack)
{
	int temp ; 
	while(!isnull(linkstack))
	{
		pop_stack(linkstack, &temp);
	}

	return 0 ; 
}

//销毁栈 
int dis_stack(linkstack_t *linkstack)
{
	clean_stack(linkstack);

	free(linkstack);

	return 0 ;
}
int main(int argc, const char *argv[])
{
	linkstack_t *linkstack = creat_stack() ; 
	if(linkstack == NULL)
	{
		printf("创建失败\n");
		return -1 ; 
	}

	int i ;
	int data ; 
	int data_top ; 
	for(i = 1; i <= 10; i++)
	{
		pust_stack(linkstack, i*10);
	}

	print_stack(linkstack);

	for(i = 1; i <= 3; i++)
	{
		pop_stack(linkstack, &data);
		printf("出栈数据为%d\n",data);
		print_stack(linkstack);
	}

	get_top_stack(linkstack, &data_top);
	printf("此时栈顶数据为%d\n",data_top);
	return 0;
}
