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

extern int key_number;

void do_irq() {

	int irq_number;
	irq_number = CPU0 .ICCIAR & 0X3FF; //读取中断号 同时通知icc 中断开始执行
	printf("irq:%d\n", irq_number);

	switch (irq_number) {
	case 58:
		mydelay_ms(20);
		if (0 == (GPX1 .DAT & (1 << 2))) {
			printf("------------>key3\n");
		}
		EXT_INT41_PEND = (1 << 2); // 清除中断源

		break;
	case 57:

		start_timer4(40, 2); // 设定 定时器延时 40sm
		//printf("key2\n");

		EXT_INT41_PEND = (1 << 1); // 清除中断源
		break;
	case 64:
		//printf("key4\n");
		start_timer4(40, 4); // 设定 定时器延时 40sm

		EXT_INT43_PEND = (1 << 2); // 清除中断源
		break;

	case 73:
		printf("timer4\n");
		switch (key_number) {
		case 2:
			if (0 == (GPX1 .DAT & (1 << 1))) {
				printf("------------>key2\n");
			} //判断按键是否按下

			break;
		case 4:
			if (0 == (GPX3 .DAT & (1 << 2))) {
				printf("----------------->key4\n");

			}
		}
		PWM .TINT_CSTAT = (PWM .TINT_CSTAT & ~(0B11111 << 5)) | (1 << 9); //清除timer4中断信号
		break;

	case 80:
		printf("key?\n");
		//清中断源

	}

	CPU0 .ICCEOIR = (CPU0 .ICCEOIR & ~0X3FF) | irq_number; //通知对应中断结

}

int main(void) {

	uart_init();
	printf("hello world!\n");

	init_timer();

	init_key();

	PWM .TCFG0 = (PWM .TCFG0 & ~(0XFF << 0)) | (99 << 0); // 100M/(99 +1) = 1M
	PWM .TCFG1 = (PWM .TCFG1 & ~(0XF << 0)) | (0B0010 << 0); // timer0 的工作频率 1M / 4 = 250Khz 每秒计数250000 次

	PWM .TCNTB0 = 478 - 1; // 计数250次  总周期1ms 频率 1Khz
	PWM .TCMPB0 = 478 / 2; // 占空比50%

	PWM .TCON = (PWM .TCON & ~(0XFF)) | (0B01010); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 1 START = 0
	PWM .TCON = (PWM .TCON & ~(0XFF)) | (0B01000); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 0 START = 0
	PWM .TCON = (PWM .TCON & ~(0XFF)) | (0B01001); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 0 START = 1

	GPD0 .CON = (GPD0 .CON & ~(0XF)) | 0X2;  // 选择tout0 输出模式
											 //	0x0 = Input
											 //	0x1 = Output
											 //	0x2 = TOUT_0

	while (1) {
		PWM .TCNTB0 = 478 - 1; // 计数250次  总周期1ms 频率 1Khz
		PWM .TCMPB0 = 478 / 2; // 占空比50%

		mydelay_ms(500);

		PWM .TCNTB0 = 426 - 1; // 计数250次  总周期1ms 频率 1Khz
		PWM .TCMPB0 = 426 / 2; // 占空比50%
		mydelay_ms(500);

		PWM .TCNTB0 = 379 - 1; // 计数250次  总周期1ms 频率 1Khz
		PWM .TCMPB0 = 379 / 2; // 占空比50%
		mydelay_ms(500);
	}

#if 0
	GPD0 .CON = (GPD0 .CON & ~(0XF)) | 0X1;

	while (1) {
		GPD0 .DAT ^= 1;
		mydelay_ms(1);
	}
#endif
	GPX2 .CON = (GPX2 .CON & ~(0XF << 28)) | (0X1 << 28);
	GPX2 .DAT &= ~(1 << 7); //熄灭 uboot 点亮的led2

	GPX1 .CON = (GPX1 .CON & ~(0XF)) | (0X1); //配置led3

	while (1) {
		GPX1 .DAT ^= 1;
		mydelay_ms(100);
		printf(">>%d\n", GPD0 .DAT & 1);

	}

	while (1)
		;
	return 0;
}
