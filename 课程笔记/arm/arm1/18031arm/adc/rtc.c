#include "exynos_4412.h"

extern int alarm_flag;

void rtc() {
	int y,year;
	beep_init();

	alarm_flag = 0;

	RTCCON = (0 << 9) | (0 << 8) | (0B0000 << 4) | (0 << 3) | (0 << 2)
			| (0 << 1) | (0 << 0);

	RTCCON |= (1 << 0);

	y = ((year % 10) << 0) | (((year / 10) % 10) << 4)
			| (((year / 100) % 10) << 8);
	RTC.BCDYEAR = y; // 0X018;//(0 << 8) | (1 << 4) |(8 << 0);

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

	//44  76  –  RTC_ALARM
	ICDISR.ICDISR2 &= ~(1 << 12); //
	ICDISER.ICDISER2 = (1 << 12); //
	ICDIPR.ICDIPR19 = (ICDIPR.ICDIPR19 & ~(0xff << 0)) | (1 << 0); //优先级设置为 1

	ICDIPTR.ICDIPTR19 = (ICDIPTR.ICDIPTR19 & ~(0xff << 0)) | (0b00000001 << 0); //设置将中断送到icc0

	ICDDCR = 1;  //启动 icd
	CPU0.ICCICR = 1; //使能icc

	while (1) {
		y = RTC.BCDYEAR;
		//			8             0x10
		year = 2000 + (y & 0xf) + ((((y & (0xf << 4))) >> 4) * 10)
				+ ((((y & (0xf << 8))) >> 8) * 100);

		printf("%4d-%02x-%02x week:%x %02x:%02x:%02x\n", year, RTC.BCDMON,
				RTC.BCDDAY, RTC.BCDWEEK, RTC.BCDHOUR, RTC.BCDMIN, RTC.BCDSEC);

		if (0 == alarm_flag) {
			mydelay_ms(500);
		} else if (1 == alarm_flag) {
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
}
