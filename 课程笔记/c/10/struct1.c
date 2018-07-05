#include <stdio.h>
struct people
{
	char sex;
	int high;
};


struct student
{
	char name[128];
	int id;
	int age;
	float score;
	struct people peo;//添加了一个结构体成员,注意该结构体必须之前已经出现过
};

int main(int argc, const char *argv[])
{
	struct student a = {"老吴",1,20,89.5,'g',170};
		
	printf("name:%s id:%d age:%d score:%.1f sex:%c high:%d\n",
			a.name,a.id,a.age,a.score,a.peo.sex,a.peo.high);
	return 0;
}
