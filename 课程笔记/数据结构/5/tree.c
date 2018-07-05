#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;//保存编号
	struct node * lchild;//保存左孩子的地址
	struct node * rchild;//保存右孩子的地址
}tree_t;//树的结点类型

//创建
tree_t * creat_tree(int num)
{
	//结束条件
	if(num  > 6)
	{
		return NULL;
	}

	//申请空间
	tree_t * root = malloc(sizeof(tree_t));

	//初始化编号，左孩子，右孩子
	root->data = num;
	root->lchild = creat_tree(num*2) ;
	root->rchild = creat_tree(num*2 + 1) ;

	return root;
}

//先序遍历(根，左，右)
void pre_tree(tree_t * root)
{
	//结束条件
	if(root == NULL)
	{
		return;
	}
	//遍历自己
	printf("%d ",root->data);

	//遍历左孩子
	pre_tree(root->lchild);

	//遍历右孩子
	pre_tree(root->rchild);
}


//中序遍历（左，根，右）
void mid_tree(tree_t * root)
{
	//结束条件
	if(root == NULL)
	{
		return;
	}

	//遍历左孩子
	mid_tree(root->lchild);

	//遍历自己
	printf("%d ", root->data);

	//遍历右孩子
	mid_tree(root->rchild);
}

//后序遍历（左，右，根）
void post_tree(tree_t * root)
{
	//结束条件
	if(root == NULL)
	{
		return;
	}

	//遍历左孩子
	post_tree(root->lchild);

	//遍历右孩子
	post_tree(root->rchild);

	//遍历自己
	printf("%d ", root->data);
}

//层次遍历
int levev_tree(tree_t * root)
{
	//创建顺序队列
	tree_t * queue[10];
	int head = 0;
	int tail = 0;

	//创建临时变量
	tree_t * temp;

	//入队根节点
	queue[tail++] = root;

	//判断队列不为空
	while(head != tail)
	{
		//出队队头元素
		temp = queue[head++];

		//打印出队数据
		printf("%d ", temp->data);

		//判断有没有左孩子，有入队
		if(temp->lchild != NULL)
		{
			queue[tail++] = temp->lchild;
		}

		//判断有没有右孩子，有入队
		if(temp->rchild != NULL)
		{
			queue[tail++] = temp->rchild;
		}
	}

	printf("\n");
}

int main(int argc, const char *argv[])
{
	tree_t * tree = creat_tree(1);

	printf("先序遍历：");
	pre_tree(tree);
	printf("\n");
	

	printf("中序遍历：");
	mid_tree(tree);
	printf("\n");

	printf("后序遍历：");
	post_tree(tree);
	printf("\n");

	printf("层次遍历：");
	levev_tree(tree);
	
	return 0;

}


