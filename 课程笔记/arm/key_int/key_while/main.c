/*
 *@brief	This example describes how to use GPIO to drive LEDs
 *@date:	02. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
 */

#include "exynos_4412.h"

/**********************************************************************
 * @brief		mydelay_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void mydelay_ms(int ms) {
	int i, j;
	while (ms--) {
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++)
				;
	}
}

/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/

int main(void) {
	GPX2.CON = (GPX2.CON & ~(0XF << 28)) | (0X1 << 28);
	GPX2 .DAT &= ~(1 << 7); //Ϩ�� uboot ������led2

	GPX1 .CON = (GPX1 .CON & ~(0XF)) | (0X1); //����led3

	GPX1 .DAT |= 1;  //��Ӧλ��1 ����
	GPX1 .DAT &= ~1; //��Ӧλ��0 ���

	GPX1 .CON = (GPX1 .CON & ~(0XF << 8)); //���� gpx1_2 Ϊ����ģʽ

	while (1) {
		if (0 == (GPX1 .DAT & (1 << 2))) { // ���͵�ƽ����

			mydelay_ms(25);				//��ʱ25ms
			if (0 == (GPX1 .DAT & (1 << 2))) { //���¼���������ǵ͵�ƽ�������ж�Ϊ��������
				GPX1 .DAT ^= 1; //led3 gpx1_0
				while (0 == (GPX1 .DAT & (1 << 2))) // �ȴ�����̧��
					;
			}
		}

	}

	while (1) {
		if (0 == (GPX1 .DAT & (1 << 2))) {
			GPX1 .DAT ^= 1;
			while (0 == (GPX1 .DAT & (1 << 2)))
				;
		}

	}

	while (1) {
		if (0 == (GPX1 .DAT & (1 << 2))) {
			GPX1 .DAT ^= 1;
			mydelay_ms(200);
		}

	}

	while (1) {
		if (0 == (GPX1 .DAT & (1 << 2))) {
			GPX1 .DAT |= 1;
		} else {
			GPX1 .DAT &= ~1;
		}
	}

	while (1)
		;
	return 0;
}
