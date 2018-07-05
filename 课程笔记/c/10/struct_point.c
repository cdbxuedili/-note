#include <stdio.h>

typedef struct student
{
	char name[128];
	int id;
	int age;
	float score;
}stu_t;

int main(int argc, const char *argv[])
{
	stu_t a = {"小红",1,20,89.5};
	stu_t *p = &a;//结构体指针,指向结构体类型的数据
	printf("name:%s id:%d age:%d score:%.1f\n",
			a.name,a.id,a.age,a.score);
	printf("name:%s id:%d age:%d score:%.1f\n",
			p->name,p->id,p->age,p->score);
	//注:指针引用成员时格式: 指针变量名->结构体成员名  (这代表取出结构体内成员)
	
	//printf("id:%d\n",(*p).id); 可以写,但不常用

	return 0;
}
