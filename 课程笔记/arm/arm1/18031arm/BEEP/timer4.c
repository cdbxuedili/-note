#include "exynos_4412.h"


void init_timer()
{

	PWM.TCFG0 = (PWM.TCFG0 & ~(0XFF << 8)) | (99 << 8); // 100M/(99 +1) = 1M
	PWM.TCFG1 = (PWM.TCFG1 & ~(0XF << 16)) | (0B0010 << 16); // timer4 �Ĺ���Ƶ�� 1M / 4 = 250Khz ÿ�����250000 ��


	PWM.TCON = (PWM.TCON & ~(0XF << 20)) | (0B0000 << 20);// RELOAD = 0 UPDATE = 0 START = 0

	PWM.TINT_CSTAT = (PWM.TINT_CSTAT & ~(0B11111 << 5)) | (1 << 4); //����timer4 �ж�

	//41  73  �C  TIMER4
	ICDISR .ICDISR2 &= ~(1 << 9);
	ICDISER .ICDISER2 = (1 << 9);
	ICDIPR .ICDIPR18 = (ICDIPR .ICDIPR18 & ~(0xff << 8)) | (1 << 8); //���ȼ�����Ϊ 1
	//(0x1 << 16);//(1 << 16);
	ICDIPTR .ICDIPTR18 = (ICDIPTR .ICDIPTR18 & ~(0xff << 8))
			| (0b00000001 << 8);	//���ý��ж��͵�icc0

	ICDDCR = 1;  //���� icd
	CPU0 .ICCICR = 1; //ʹ��icc

}

int  key_number;
void start_timer4(int ms,int key_n)
{
	key_number = key_n;
	PWM.TCNTB4 = 250 * ms; //���������� �� ��1 / 250K�� * 250000 = 1S  ���� timer����1s�������ж�

	PWM.TCON = (PWM.TCON & ~(0XF << 20)) | (0B0110 << 20);// RELOAD = 1 UPDATE = 1 START = 0
	PWM.TCON = (PWM.TCON & ~(0XF << 20)) | (0B0100 << 20);// RELOAD = 1 UPDATE = 0 START = 0
	PWM.TCON = (PWM.TCON & ~(0XF << 20)) | (0B0001 << 20);// RELOAD = 0 UPDATE = 0 START = 1
}
