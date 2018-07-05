#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	int *data;//存数据
	int size;//保存元素个数
	int top;//栈顶
}stack_tt;//栈的数据类型

//创建
stack_tt * creat_stack(int size)
{
	//申请空间
	stack_tt * stack = malloc(sizeof(stack_tt));
	if(stack == NULL)
	{
		return NULL;
	}
	//初始化
	stack->data = malloc(sizeof(int) * size);

	stack->size = size;

	stack->top = -1;//栈空

	return stack;
}

//判满 
int isfull(stack_tt * stack)
{
	return stack->top == (stack->size - 1);
}

//判空 
int isnull(stack_tt * stack)
{
	return stack->top == -1;
}

//进栈 (尾部增加)
int push_stack(stack_tt *stack, int data)
{
	//判断实施条件
	if(isfull(stack))
	{
		return -1 ; 
	}

	//数据入栈
	stack->data[stack->top+1] = data ;   

	//修改top 
	stack->top++ ;    

	return 0 ; 
}

//出栈 (尾删)
int pop_stack(stack_tt *stack, int *data)
{
	//判断实施条件
	if(isnull(stack))
	{
		return -1 ; 
	}

	//获取出栈数据 
	*data = stack->data[stack->top] ; 

    //修改top ，删除数据 
	stack->top-- ;  

	return 0 ; 
}

//获取栈顶数据 
int get_top_stack(stack_tt *stack, int *data)
{
	//判断实施条件
	if(isnull(stack))
	{
		return -1 ; 
	}

	//获取栈顶数据
	*data = stack->data[stack->top] ; 

	return 0 ; 
}
//打印数据 
int print_stack(stack_tt *stack)
{
	if(isnull(stack))
	{
		return -1 ; 
	}
	int i ; 
	printf("栈顶\n");
	for(i = stack->top; i >= 0; i--)
	{
		printf("%d\n", stack->data[i]);
	}
	printf("栈底\n");

	return 0 ; 
}

//清空栈 
int clean_stack(stack_tt *stack)
{
	stack->top = -1 ; 

	return 0 ; 
}


//销毁
int dis_stack(stack_tt *stack)
{
	free(stack->data);
	free(stack);
	return 0 ; 
}

int main(int argc, const char *argv[])
{
	stack_tt * stack = creat_stack(10);
	if(stack == NULL)
	{
		return -1;
	}
	int i;
	for( i = 1; i <= 10; i++)
	{
		push_stack(stack, i*10);
	}
	print_stack(stack);

	int data ; 
	for(i = 1; i <= 3; i++)
	{
		pop_stack(stack, &data);
		printf("出栈数据为:%d\n", data);
		print_stack(stack);
	}

	int data_top;
	get_top_stack(stack, &data_top);
	printf("栈顶数据：%d\n", data_top );
	
	return 0;
}
