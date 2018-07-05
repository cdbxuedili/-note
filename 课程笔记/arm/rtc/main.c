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
	irq_number = CPU0 .ICCIAR & 0X3FF; //��ȡ�жϺ� ͬʱ֪ͨicc �жϿ�ʼִ��
	printf("irq:%d\n", irq_number);

	switch (irq_number) {
	case 58:
		mydelay_ms(20);
		if (0 == (GPX1 .DAT & (1 << 2))) {
			printf("------------>key3\n");
			if(PWM .TCMPB1 < 240)
			PWM .TCMPB1 += 10;
		}
		EXT_INT41_PEND = (1 << 2); // ����ж�Դ

		break;
	case 57:

		start_timer4(40, 2); // �趨 ��ʱ����ʱ 40sm
		//printf("key2\n");

		EXT_INT41_PEND = (1 << 1); // ����ж�Դ
		break;
	case 64:
		//printf("key4\n");
		start_timer4(40, 4); // �趨 ��ʱ����ʱ 40sm

		EXT_INT43_PEND = (1 << 2); // ����ж�Դ
		break;

	case 73:
		printf("timer4\n");
		switch (key_number) {
		case 2:
			if (0 == (GPX1 .DAT & (1 << 1))) {
				printf("------------>key2\n");
				if(PWM .TCMPB1 > 10)
					PWM .TCMPB1 -= 10;
			} //�жϰ����Ƿ���

			break;
		case 4:
			if (0 == (GPX3 .DAT & (1 << 2))) {
				printf("----------------->key4\n");
				alarm_flag = 0;//beep_stop();
			}
		}
		PWM .TINT_CSTAT = (PWM .TINT_CSTAT & ~(0B11111 << 5)) | (1 << 9); //���timer4�ж��ź�
		break;

	case 76:

		printf("-------------------->alarm\n");
		alarm_flag = 1;//beep_start();
		RTCINTP	= (1 << 1);
		break;


	case 80:
		printf("key?\n");
		//���ж�Դ

	}

	CPU0 .ICCEOIR = (CPU0 .ICCEOIR & ~0X3FF) | irq_number; //֪ͨ��Ӧ�жϽ�

}

int main(void) {

	int y,year = 2018;

	uart_init();
	printf("hello world!\n");

	init_timer();
	init_key();

	beep_init();

	alarm_flag = 0;

	RTCCON =  (0 << 9) | (0 << 8) | (0B0000 << 4) | (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0);

	RTCCON |= (1 << 0);

	y = ((year % 10) << 0) | (((year / 10) % 10) << 4) | (((year / 100) % 10) << 8);
	RTC.BCDYEAR = y;// 0X018;//(0 << 8) | (1 << 4) |(8 << 0);

	RTC.BCDMON = 0X04;
	RTC.BCDDAY = 0X27;
	RTC.BCDWEEK = 0X16;
	RTC.BCDHOUR = 0X09;
	RTC.BCDMIN = 0X59;
	RTC.BCDSEC = 0X57;

	RTCCON &= ~(1 << 0);


	RTCCON |= (1 << 0);

	RTCALM.ALM = (1 << 6) | (1 << 0);
	RTCALM.SEC = 0x03;

	RTCCON &= ~(1 << 0);

	//44  76  �C  RTC_ALARM
	ICDISR .ICDISR2 &= ~(1 << 12); //
	ICDISER .ICDISER2 = (1 << 12); //
	ICDIPR .ICDIPR19 = (ICDIPR .ICDIPR19 & ~(0xff << 0)) | (1 << 0); //���ȼ�����Ϊ 1

	ICDIPTR .ICDIPTR19 = (ICDIPTR .ICDIPTR19 & ~(0xff << 0))
			| (0b00000001 << 0); //���ý��ж��͵�icc0

	ICDDCR = 1;  //���� icd
	CPU0 .ICCICR = 1; //ʹ��icc




	while(1){
		y = RTC.BCDYEAR;
		//			8             0x10
		year = 2000 + (y & 0xf) + ( (((y & (0xf << 4)) ) >> 4) * 10 ) +  ( (((y & (0xf << 8)) ) >> 8) * 100 );

		printf("%4d-%02x-%02x week:%x %02x:%02x:%02x\n",year,RTC.BCDMON,RTC.BCDDAY,RTC.BCDWEEK,
				RTC.BCDHOUR,RTC.BCDMIN,RTC.BCDSEC);

		if(0 == alarm_flag){
			mydelay_ms(500);
		}else if(1 == alarm_flag)
		{
			beep_start();
			mydelay_ms(100);
			beep_stop();
			mydelay_ms(50);
			beep_start();
			mydelay_ms(100);
			beep_stop();
			mydelay_ms(200);
		}

	}





	while (1)
		;
	return 0;
}
