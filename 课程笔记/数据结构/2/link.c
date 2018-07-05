#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;//存储数据
	struct node * next;//指向下一个结点的地址
}link_t;//链表的结点类型

//创建
link_t * creat_link()
{
	//申请空间
	link_t * head = malloc(sizeof(link_t));
	if(head == NULL)
	{
		printf("空间申请失败!\n");
		return NULL;
	}

	//初始化
	head->next = NULL;

	//返回申请空间的首地址
	return head;
}

//判空
int isnull(link_t * head)
{
	return head->next == NULL;
}

//增加数据
int ins_head_link(link_t * head, int data)
{
	//申请新结点的存储空间
	link_t * newnode = malloc(sizeof(link_t));

	//存入数据
	newnode->data = data;

	//将新结点连入到链表中，顺序不能颠倒
	newnode->next = head->next;
	head->next = newnode;

	return 0;
}


//指定位置增加数据
int ins_index_link(link_t * head, int data, int index)
{
	//位置过小
	if(index < 0 )
	{
		printf("增加数据，指定位置过小!\n");
		return -1;
	}

	//偏移位置
	while(index--)
	{
		head = head->next;
		if(head == NULL)
		{
			printf("增加数据，指定位置过大!\n");
			return -1;
		}
	}

	ins_head_link(head, data);

	return 0;
}
//删除数据
int del_head_link(link_t * head)
{
	//判断实施条件
	if(isnull(head))
	{
		printf("链表为空，无法执行删除操作!\n");
		return -1;
	}

	//标记要删除的结点
	link_t * temp = head->next;

	//删除结点
	head->next = temp->next;

	//释放删除的结点
	free(temp);
	
	return 0;
}

//指定位置删除数据
int del_index_link(link_t * head, int index)
{
	//位置过小
	if(index < 0 || isnull(head))
	{
		printf("删除数据，指定位置过小!\n");
		return -1;
	}

	//偏移位置
	while(index--)
	{
		head = head->next;
		if(head->next == NULL)
		{
			printf("删除数据，指定位置过大!\n");
			return -1;
		}
	}

	del_head_link(head);

	return 0;
}

//打印数据
int print_link(link_t * head)
{
	//判断实施条件
	if(isnull(head))
	{
		printf("链表为空，无法执行打印操作!\n");
		return -1;
	}

	//跳过头结点打印数据
	head = head->next;
	while(head != NULL)
	{
		printf("%d ", head->data);
		head = head->next;
	}

	printf("\n");

	return 0;
}

//修改数据
int change_link(link_t * head, int data, int index)
{
	//位置过小
	if(index < 0 || isnull(head))
	{
		printf("修改数据，指定位置过小!\n");
		return -1;
	}

	//偏移位置
	while(index--)
	{
		head = head->next;
		if(head->next == NULL)
		{
			printf("修改数据，指定位置过大！\n");
			return -1;
		}
	}

	//修改数据
	head->next->data = data;

	return 0;
}

//查找数据
link_t * locate_link(link_t * head, int data)
{
	while(head->next != NULL)
	{
		if(head->next->data == data)
		{
			return head;
		}
		head = head->next;
	}

	printf("表中没有改数据!\n");
	return NULL;
}

//清空
int clean_link(link_t * head)
{
	while(!isnull(head))
	{
		del_head_link(head);
	}

	return 0;
}
//销毁
int dis_link(link_t * head)
{
	clean_link(head);
	free(head);

	return 0;
}
//逆打印1	
int reprint_link(link_t * head)
{
	//创建临时链表
	link_t * temp = creat_link();

	//临时链表从头增加数据
	while(head->next != NULL)
	{
		ins_head_link(temp, head->next->data);
		head = head->next;
	}

	//打印临时链表
	print_link(temp);

	//销毁临时链表
	dis_link(temp);

	return 0;
}

//逆打印2(递归实现)
void reprint1_link(link_t * head)
{
	//递归结束条件
	if(head->next == NULL)
	{
		return ;
	}

	reprint1_link(head->next);

	printf("%d ", head->next->data);

}

int main(int argc, const char *argv[])
{
	link_t * link = creat_link();
	if(link == NULL)
	{
		return -1;
	}

	int i;
	for(i = 1; i <= 20; i++)
	{
		ins_head_link(link, i * 10);
	}

	print_link(link);

	for(i = 1; i <= 10; i++)
	{
		del_head_link(link);
	}
	print_link(link);

	ins_index_link(link, 666, 6);
	print_link(link);

	del_index_link(link, 6);
	print_link(link);

	change_link(link, 666, 6);
	print_link(link);

	link_t * ret = locate_link(link, 666);
	del_head_link(ret);
	print_link(link);

	reprint_link(link);
	reprint1_link(link);
	printf("\n");


	clean_link(link);
	print_link(link);
	
	dis_link(link);

	return 0;
}
