#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};

	int i,j,k;
	int max,min;//假设每行最大,以及每列最小
	int flagh,flagl;//记录每行真正最大值和每列真正最小值所在的位置
	for(i = 0;i < 3;i++)
	{
		max = a[i][0];
		flagl = 0;
		for(j = 0;j < 4;j++)//找到每行中真正的最大值并记录下标(列标)
		{
			if(max < a[i][j])
			{
				max = a[i][j];
				flagl = j;
			}
		}
        
		min = a[i][flagl];
		flagh = i;
		for(k = 0;k < 3;k++)//找到对应列的最小值
		{
			if(min > a[k][flagl])
			{
				min = a[k][flagl];
				flagh = k;
			}
		}

		if(i == flagh)
		{
			printf("a[%d][%d] = %d\n",flagh,flagl,a[flagh][flagl]);
		}



	}




	return 0;
}


