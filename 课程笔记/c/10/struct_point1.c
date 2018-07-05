#include <stdio.h>

typedef struct student
{
	char name[128];
	int id;
	int age;
	float score;
	struct student *p;//封装的结构体指针指向的类型就是当前的结构体
}stu_t;


int main(int argc, const char *argv[])
{
	stu_t b = {"小红",2,21,90.5,&b};
	stu_t a = {"小明",1,20,89.5,&b};
	stu_t *p = &b;
	printf("b_id:%d\n",b.id);
	printf("b_id:%d\n",p->id);
	printf("b_id:%d\n",a.p->id);
	printf("b_id:%d\n",b.p->id);
	printf("b_id:%d\n",b.p->p->p->id);
	return 0;
}
