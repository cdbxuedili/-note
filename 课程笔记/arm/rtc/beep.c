#include "exynos_4412.h"

void beep_init() {
	PWM .TCFG0 = (PWM .TCFG0 & ~(0XFF << 0)) | (99 << 0); // 100M/(99 +1) = 1M
	PWM .TCFG1 = (PWM .TCFG1 & ~(0XFF << 0)) | (0B0010 << 0); // timer0 �Ĺ���Ƶ�� 1M / 4 = 250Khz ÿ�����250000 ��

	PWM .TCNTB0 = 250 - 1; // ����250��  ������1ms Ƶ�� 1Khz
	PWM .TCMPB0 = 250 / 2; // ռ�ձ�50%

	PWM .TCON = (PWM .TCON & ~(0XF << 0)) | (0B0000 << 0); // DEAD = 0 RELOAD = 0 Inverter = 0  UPDATE = 0 START = 0


	GPD0 .CON = (GPD0 .CON & ~(0XF << 0));  // ѡ��INPUT ���ģʽ

}

void beep_start() {
	PWM .TCON = (PWM .TCON & ~(0XFF << 0)) | (0B1010 << 0); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 1 START = 0
	PWM .TCON = (PWM .TCON & ~(0XFF << 0)) | (0B1000 << 0); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 0 START = 0
	PWM .TCON = (PWM .TCON & ~(0XFF << 0)) | (0B1001 << 0); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 0 START = 1
	GPD0 .CON = (GPD0 .CON & ~(0XF << 0)) | (0X2 << 0);  // ѡ��tout0 ���ģʽ
}

void beep_stop() {
	PWM .TCON = (PWM .TCON & ~(0XFF << 0)) | (0B0000 << 0); // DEAD = 0 RELOAD = 0 Inverter = 0  UPDATE = 0 START = 0
	GPD0 .CON = (GPD0 .CON & ~(0XF << 0));  // ѡ��INPUT ���ģʽ
}


void music()
{
	int i = 1000;
	while(i --)
		;
}
