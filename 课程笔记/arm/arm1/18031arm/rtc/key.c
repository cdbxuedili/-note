#include "exynos_4412.h"

void init_key() {
//--------------------key4--------------------------------
	GPX3 .CON = (GPX3 .CON & ~(0XF << 8)) | (0xf << 8); //

	EXT_INT43_CON = (EXT_INT43_CON & ~(0xf << 8)) | (0x2 << 8); //下降沿触发中断事件

	EXT_INT43_FLTCON0 |= (1 << 23); // 设置中断滤波 使能，滤除部分抖动
	EXT_INT43_FLTCON0 &= ~(1 << 23); //选择延时滤波

	EXT_INT43_MASK &= ~(1 << 2); //使能中断

	//GPX3_2 EXT_INT43[2]>> XEINT[26] >> 32  64  –  EINT16_31
	//1.中断使能  2.中断安全   3.中断优先级 4.中断类型irq/fiq 5.cpu选择

	ICDISR .ICDISR2 &= ~(1 << 0); //
	ICDISER .ICDISER2 = (1 << 0); //
	ICDIPR .ICDIPR16 = (ICDIPR .ICDIPR16 & ~(0xff << 0)) | (1 << 0); //优先级设置为 1

	ICDIPTR .ICDIPTR16 = (ICDIPTR .ICDIPTR16 & ~(0xff << 0))
			| (0b00000001 << 0); //设置将中断送到icc0

	ICDDCR = 1;  //启动 icd
	CPU0 .ICCICR = 1; //使能icc

//--------------------key2--------------------------------
	GPX1 .CON = (GPX1 .CON & ~(0XF << 4)) | (0xf << 4); //设置 gpx1_1为外部中断模式EXT_INT41[1] key2

	EXT_INT41_CON = (EXT_INT41_CON & ~(0xf << 4)) | (0x2 << 4); //下降沿触发中断事件

	EXT_INT41_FLTCON0 |= (1 << 15); // 设置中断滤波 使能，滤除部分抖动
	EXT_INT41_FLTCON0 &= ~(1 << 14); //选择延时滤波

	EXT_INT41_MASK &= ~(1 << 1); //使能中断

	//GPX1_1 EXT_INT41[1]>> XEINT[9] >> 25  57  –  EINT[9]  External Interrupt
	//1.中断使能  2.中断安全   3.中断优先级 4.中断类型irq/fiq 5.cpu选择

	ICDISR .ICDISR1 &= ~(1 << 25); //设置58号中断为安全模式
	ICDISER .ICDISER1 = (1 << 25); //将26位置1 使能58号中断
	ICDIPR .ICDIPR14 = (ICDIPR .ICDIPR14 & ~(0xff << 8)) | (1 << 8); //优先级设置为 1
	//(0x1 << 16);//(1 << 16);
	ICDIPTR .ICDIPTR14 = (ICDIPTR .ICDIPTR14 & ~(0xff << 8))
			| (0b00000001 << 8);	//设置将中断送到icc0

	ICDDCR = 1;  //启动 icd
	CPU0 .ICCICR = 1; //使能icc

//-----------------------------key3-----------------------------------------------------------------

	GPX1 .CON = (GPX1 .CON & ~(0XF << 8)) | (0xf << 8); //设置 gpx1_2 为外部中断模式EXT_INT41[2] key3

	EXT_INT41_CON = (EXT_INT41_CON & ~(0xf << 8)) | (0x2 << 8); //下降沿触发中断事件

	EXT_INT41_FLTCON0 |= (1 << 23); // 设置中断滤波 使能，滤除部分抖动
	EXT_INT41_FLTCON0 &= ~(1 << 22); //选择延时滤波

	EXT_INT41_MASK &= ~(1 << 2); //使能中断
	//GPX1_2 EXT_INT41[2]>> XEINT[10] >> SPI:26  ID:58  –  EINT[10]  External Interrupt

	//1.中断使能  2.中断安全   3.中断优先级 4.中断类型irq/fiq 5.cpu选择

	ICDISR .ICDISR1 &= ~(1 << 26); //设置58号中断为安全模式
	ICDISER .ICDISER1 = (1 << 26); //将26位置1 使能58号中断
	ICDIPR .ICDIPR14 = (ICDIPR .ICDIPR14 & ~(0xff << 16)) | (1 << 16); //优先级设置为 1
	//(0x1 << 16);//(1 << 16);
	ICDIPTR .ICDIPTR14 = (ICDIPTR .ICDIPTR14 & ~(0xff << 16))
			| (0b00000001 << 16);	//设置将中断送到icc0

	ICDDCR = 1;  //启动 icd
	CPU0 .ICCICR = 1; //使能icc
}
