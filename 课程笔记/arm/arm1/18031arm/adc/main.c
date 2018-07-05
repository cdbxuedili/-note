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

int alarm_flag;
void do_irq() {

	int irq_number;
	irq_number = CPU0 .ICCIAR & 0X3FF; //读取中断号 同时通知icc 中断开始执行
	printf("irq:%d\n", irq_number);

	switch (irq_number) {
	case 58:
		mydelay_ms(20);
		if (0 == (GPX1 .DAT & (1 << 2))) {
			printf("------------>key3\n");
			if (PWM .TCMPB1 < 240)
				PWM .TCMPB1 += 10;
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
				if (PWM .TCMPB1 > 10)
					PWM .TCMPB1 -= 10;
			} //判断按键是否按下

			break;
		case 4:
			if (0 == (GPX3 .DAT & (1 << 2))) {
				printf("----------------->key4\n");
				alarm_flag = 0; //beep_stop();
			}
		}
		PWM .TINT_CSTAT = (PWM .TINT_CSTAT & ~(0B11111 << 5)) | (1 << 9); //清除timer4中断信号
		break;

	case 76:

		printf("-------------------->alarm\n");
		alarm_flag = 1; //beep_start();
		RTCINTP = (1 << 1);
		break;

	case 80:
		printf("key?\n");
		//清中断源

	}

	CPU0 .ICCEOIR = (CPU0 .ICCEOIR & ~0X3FF) | irq_number; //通知对应中断结

}

int main(void) {

	int val,c;

	uart_init();
	printf("hello world!\n");

	init_timer();
	init_key();

	ADCCON = (1 << 16) | (1 << 14) | (123 << 6) | (0 << 2) | (0 << 1)
			| (0 << 0);

	ADCMUX = 0b0011;//3;

	WDT.WTCNT = 3000;
	WDT.WTCON = (255 << 8) | (1 << 5) | (0b11 <<3) | (0 <<2) | (1 << 0) ;//初始化看门狗

	while (1) {
		WDT.WTCNT = 3000;//喂狗
		ADCCON |= 1;

		while (0 == (ADCCON & (1 << 15)))
			;

		val = ADCDAT & 0xfff;

		printf("%d\n", val);
		printf("%dmV\n", (val * 1800) / 4096);
		c = (3430 - val)/15;
		printf("%d°\n",c);
		mydelay_ms(200);
	}

	while (1)
		;
	return 0;
}
