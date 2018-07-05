#include <stdio.h>




int main(int argc, const char *argv[])
{
	int money = 1000000;
	int money_del = 0;
	int money_now = 0;
	int money_add = 0;
	int cmd = 0;
	printf("1.查询 2.取款 3.存款 4.退卡 \n");
	scanf("%d",&cmd);
	
	switch(cmd)
	{
		case 1:
			printf("您现有余额%d元\n",money);
			break;
		case 2:
			printf("请输入取款金额:\n");
			scanf("%d",&money_del);
			if(money_del > money)
			{
				printf("余额不足,退出程序!\n");
				return -1;
			}
			money_now = money - money_del;
			printf("取款成功,您现有余额%d元\n",money_now);
			break;
		case 3:
			printf("请输入存款金额\n");
			scanf("%d",&money_add);
			money_now = money + money_add;
			printf("存款成功,现有余额%d元\n",money_now);
			break;
		case 4:
			printf("退卡成功!\n");
			break;
		default:
			printf("输入指令有误,程序退出!\n");
			return -1;
	}



	return 0;
}
