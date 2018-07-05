#include "exynos_4412.h"


void init_timer()
{

	PWM.TCFG0 = (PWM.TCFG0 & ~(0XFF << 8)) | (99 << 8); // 100M/(99 +1) = 1M
	PWM.TCFG1 = (PWM.TCFG1 & ~(0XF << 16)) | (0B0010 << 16); // timer4 的工作频率 1M / 4 = 250Khz 每秒计数250000 次


	PWM.TCON = (PWM.TCON & ~(0XF << 20)) | (0B0000 << 20);// RELOAD = 0 UPDATE = 0 START = 0

	PWM.TINT_CSTAT = (PWM.TINT_CSTAT & ~(0B11111 << 5)) | (1 << 4); //启动timer4 中断

	//41  73  –  TIMER4
	ICDISR .ICDISR2 &= ~(1 << 9);
	ICDISER .ICDISER2 = (1 << 9);
	ICDIPR .ICDIPR18 = (ICDIPR .ICDIPR18 & ~(0xff << 8)) | (1 << 8); //优先级设置为 1
	//(0x1 << 16);//(1 << 16);
	ICDIPTR .ICDIPTR18 = (ICDIPTR .ICDIPTR18 & ~(0xff << 8))
			| (0b00000001 << 8);	//设置将中断送到icc0

	ICDDCR = 1;  //启动 icd
	CPU0 .ICCICR = 1; //使能icc

}

int  key_number;
void start_timer4(int ms,int key_n)
{
	key_number = key_n;
	PWM.TCNTB4 = 250 * ms; //计数总周期 ： （1 / 250K） * 250000 = 1S  ：即 timer启动1s后会产生中断

	PWM.TCON = (PWM.TCON & ~(0XF << 20)) | (0B0110 << 20);// RELOAD = 1 UPDATE = 1 START = 0
	PWM.TCON = (PWM.TCON & ~(0XF << 20)) | (0B0100 << 20);// RELOAD = 1 UPDATE = 0 START = 0
	PWM.TCON = (PWM.TCON & ~(0XF << 20)) | (0B0001 << 20);// RELOAD = 0 UPDATE = 0 START = 1
}
