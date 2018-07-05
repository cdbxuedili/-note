#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;//数据域
	struct node * front;//存储前一个结点的地址
	struct node * next;//存储后一个结点的地址
}dblink_t;//双链的结点类型

dblink_t * creat_dblink()
{
	//申请头尾结点的存储空间
	dblink_t * head = malloc(sizeof(dblink_t));
	dblink_t * tail = malloc(sizeof(dblink_t));
	if(head == NULL || tail == NULL)
	{
		printf("空间申请失败!\n");
		return NULL;
	}

	//初始化
	head->next = tail;
	head->front = NULL;
	tail->next = NULL;
	tail->front = head;

	//返回头结点的地址
	return head;
}

//判空
int isnull(dblink_t * head)
{
	return head->next->next == NULL;
}

//从头增加数据
int ins_head_dblink(dblink_t * head, int data)
{
	//申请新结点存储空间
	dblink_t * newnode = malloc(sizeof(dblink_t));

	//存入数据
	newnode->data = data;

	//链接到链表中
	//先修改新结点的前驱和后继
	newnode->next = head->next;
	newnode->front = head;

	//再修改头尾结点的后继和前驱
	head->next = newnode;
	newnode->next->front = newnode;

#if 0
	head->next->front = newnode;
	head->next = newnode;

	newnode->front->next = newnode;
	newnode->next->front = newnode;
#endif
	return 0;
}
//从头删除数据
int del_head_dblink(dblink_t * head)
{
	//判断实施条件
	if(isnull(head))
	{
		printf("表为空，无法执行删除操作!\n");
		return -1;
	}

	//备份删除结点的地址
	dblink_t * temp = head->next;

	//删除数据
	head->next = temp->next;
	temp->next->front = head;

	//释放删除数据的地址
	free(temp);

	return 0;
}


//打印数据
int print_dblink(dblink_t * head)
{
	//判断实施条件
	if(isnull(head))
	{
		return -1;
	}
	//正向打印
	printf("正向打印：");
	while(head->next->next != NULL)
	{
		head = head->next;
		printf("%d ", head->data);
	}
	printf("\n");


	//反向打印
	printf("反向打印：");
	while(head->front != NULL)
	{
		printf("%d ", head->data);
		head = head->front;
	}
	printf("\n");

	return 0;
}
int main(int argc, const char *argv[])
{
	dblink_t * dblink = creat_dblink();
	if(dblink == NULL)
	{
		return -1;
	}
	print_dblink(dblink);

	int i;
	for(i = 1; i <= 20; i++)
	{
		ins_head_dblink(dblink, i * 10);
	}
	print_dblink(dblink);


	return 0;
}
