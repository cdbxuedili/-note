#include "exynos_4412.h"

void beep_init() {
	PWM .TCFG0 = (PWM .TCFG0 & ~(0XFF << 0)) | (99 << 0); // 100M/(99 +1) = 1M
	PWM .TCFG1 = (PWM .TCFG1 & ~(0XFF << 0)) | (0B0010 << 0); // timer0 的工作频率 1M / 4 = 250Khz 每秒计数250000 次

	PWM .TCNTB0 = 250 - 1; // 计数250次  总周期1ms 频率 1Khz
	PWM .TCMPB0 = 250 / 2; // 占空比50%

	PWM .TCON = (PWM .TCON & ~(0XF << 0)) | (0B0000 << 0); // DEAD = 0 RELOAD = 0 Inverter = 0  UPDATE = 0 START = 0


	GPD0 .CON = (GPD0 .CON & ~(0XF << 0));  // 选择INPUT 输出模式

}

void beep_start() {
	PWM .TCON = (PWM .TCON & ~(0XFF << 0)) | (0B1010 << 0); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 1 START = 0
	PWM .TCON = (PWM .TCON & ~(0XFF << 0)) | (0B1000 << 0); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 0 START = 0
	PWM .TCON = (PWM .TCON & ~(0XFF << 0)) | (0B1001 << 0); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 0 START = 1
	GPD0 .CON = (GPD0 .CON & ~(0XF << 0)) | (0X2 << 0);  // 选择tout0 输出模式
}

void beep_stop() {
	PWM .TCON = (PWM .TCON & ~(0XFF << 0)) | (0B0000 << 0); // DEAD = 0 RELOAD = 0 Inverter = 0  UPDATE = 0 START = 0
	GPD0 .CON = (GPD0 .CON & ~(0XF << 0));  // 选择INPUT 输出模式
}


void music()
{
	int i = 1000;
	while(i --)
		;
}
