#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

typedef struct list
{
	int data[SIZE];//数据存放的位置
	int last;//标记表中最后一位有效数据的位置
}list_t;//顺序表的类型



//创建表
list_t * creat_list()
{
	list_t * list = malloc(sizeof(list_t));//申请空间
	if(list == NULL)//判断实施条件
	{
		printf("空间申请失败!\n");
		return NULL;	
	}

	list->last = -1;//初始化，代表表中没有有效数据

	return list;//返回申请空间的首地址
}
//判满
int isfull(list_t * list)
{
	return list->last == (SIZE - 1);
}

//判空
int isnull(list_t * list)
{
	return list->last == -1;
}

//增加数据
int ins_head_list(list_t * list, int data)
{
	//判断实施条件
	if(isfull(list))
	{
		printf("表为满，无法执行插入操作!\n");
		return -1;
	}

	//挪出位置
	int i;
	for(i = list->last; i >= 0; i--)
	{
		list->data[i+1] = list->data[i];
	}

	//增加数据
	list->data[0] = data;

	//修改last的值
	list->last++;

	return 0;
}

//指定位置增加数据
int ins_index_list(list_t * list, int data, int index)
{
	//判断实施条件
	if(isfull(list) || index < 0 || index > list->last+1)
	{
		printf("增加数据，指定位置出错!\n");
		return -1;
	}

	//挪出位置
	int i;
	for(i = list->last; i >= index; i--)
	{
		list->data[i+1] = list->data[i];
	}

	//指定位置存入数据
	list->data[index] = data;

	//修改last的值
	list->last++;

	return 0;
}
//删除数据
int del_head_list(list_t * list)
{
	//判断实施条件
	if(isnull(list))
	{
		printf("表为空，无法执行删除操作!\n");
		return -1;
	}

	//删除数据
	int i;
	for(i = 0; i < list->last; i++)
	{
		list->data[i] = list->data[i+1];
	}

	//修改last的值
	list->last--;

	return 0;
}

//指定位置删除数据
int del_index_list(list_t * list, int index)
{
	//判断实施条件
	if(isnull(list) || index < 0 || index > list->last)
	{
		printf("删除数据，指定位置出错!\n");
		return -1;
	}

	//删除数据
	int i;
	for(i = index; i < list->last; i++)
	{
		list->data[i] = list->data[i+1];
	}

	//修改last的值
	list->last--;

	return 0;
}

//打印数据
int print_list(list_t * list)
{
	//判断实施条件
	if(isnull(list))
	{
		printf("表为空，无法执行打印操作!\n");
		return -1;
	}

	int i;
	for(i = 0; i <= list->last; i++)
	{
		printf("%d ",list->data[i] );
	}

	printf("\n");

	return 0;
}

//修改数据
int change_list(list_t * list, int data, int index)
{
	//判断实施条件
	if(isnull(list) || index < 0 || index > list->last)
	{
		printf("修改数据，指定位置出错!\n");
		return -1;	
	}

	//指定位置修改数据
	list->data[index] = data;

	return 0;
}

//查找数据
int locate_list(list_t * list, int data)
{
	//判断实施条件
	if(isnull(list))
	{
		return -1;
	}

	//遍历表，查找数据，返回位置
	int i;
	for(i = 0; i <= list->last; i++)
	{
		if(list->data[i] == data)
		{
			return i;
		}
	}

	//提示操作者没有找到
	printf("表中没有该数据!\n");
	return -1;
}

//清空
int clean_list(list_t * list)
{
	list->last = -1;
	return 0;
}

//销毁
int dis_list(list_t * list)
{
	free(list);
	return 0;
}

int main(int argc, const char *argv[])
{
	list_t * list = creat_list();
	if(list == NULL)
	{
		printf("creat_list执行失败!\n");
		return -1;
	}
	
	int i;
	for(i = 1; i <= 20; i++)
	{
		if(ins_head_list(list, i*10)== 0)
			print_list(list);
	}
	
	for(i = 1; i <= 10; i++)
	{
		if(del_head_list(list) == 0)
			print_list(list);
	}
	
	ins_index_list(list, 666, 6);
	print_list(list);

	del_index_list(list, 6);
	print_list(list);

	change_list(list, 666, 6);
	print_list(list);

	int ret = locate_list(list, 666);
	printf("位置：%d\n", ret);
	
	clean_list(list);
	print_list(list);

	dis_list(list);	
	return 0;
}
