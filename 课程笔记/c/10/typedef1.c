#include <stdio.h>
#include <string.h>


typedef struct student
{
	char name[128];     
	int id;
	int age;
	float score;
}stu_t;  
//struct student == stu_t

int main(int argc, const char *argv[])
{

	struct student a = {"小明",1,20,89.5};
	stu_t b;//struct student b;
	b = a;
	printf("name:%s id:%d age:%d score:%.1f\n"
			,a.name,a.id,a.age,a.score);
	printf("name:%s id:%d age:%d score:%.1f\n"
			,b.name,b.id,b.age,b.score);



	return 0;
}
