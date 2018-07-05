#include "exynos_4412.h"

void init_key() {
//--------------------key4--------------------------------
	GPX3 .CON = (GPX3 .CON & ~(0XF << 8)) | (0xf << 8); //

	EXT_INT43_CON = (EXT_INT43_CON & ~(0xf << 8)) | (0x2 << 8); //�½��ش����ж��¼�

	EXT_INT43_FLTCON0 |= (1 << 23); // �����ж��˲� ʹ�ܣ��˳����ֶ���
	EXT_INT43_FLTCON0 &= ~(1 << 23); //ѡ����ʱ�˲�

	EXT_INT43_MASK &= ~(1 << 2); //ʹ���ж�

	//GPX3_2 EXT_INT43[2]>> XEINT[26] >> 32  64  �C  EINT16_31
	//1.�ж�ʹ��  2.�жϰ�ȫ   3.�ж����ȼ� 4.�ж�����irq/fiq 5.cpuѡ��

	ICDISR .ICDISR2 &= ~(1 << 0); //
	ICDISER .ICDISER2 = (1 << 0); //
	ICDIPR .ICDIPR16 = (ICDIPR .ICDIPR16 & ~(0xff << 0)) | (1 << 0); //���ȼ�����Ϊ 1

	ICDIPTR .ICDIPTR16 = (ICDIPTR .ICDIPTR16 & ~(0xff << 0))
			| (0b00000001 << 0); //���ý��ж��͵�icc0

	ICDDCR = 1;  //���� icd
	CPU0 .ICCICR = 1; //ʹ��icc

//--------------------key2--------------------------------
	GPX1 .CON = (GPX1 .CON & ~(0XF << 4)) | (0xf << 4); //���� gpx1_1Ϊ�ⲿ�ж�ģʽEXT_INT41[1] key2

	EXT_INT41_CON = (EXT_INT41_CON & ~(0xf << 4)) | (0x2 << 4); //�½��ش����ж��¼�

	EXT_INT41_FLTCON0 |= (1 << 15); // �����ж��˲� ʹ�ܣ��˳����ֶ���
	EXT_INT41_FLTCON0 &= ~(1 << 14); //ѡ����ʱ�˲�

	EXT_INT41_MASK &= ~(1 << 1); //ʹ���ж�

	//GPX1_1 EXT_INT41[1]>> XEINT[9] >> 25  57  �C  EINT[9]  External Interrupt
	//1.�ж�ʹ��  2.�жϰ�ȫ   3.�ж����ȼ� 4.�ж�����irq/fiq 5.cpuѡ��

	ICDISR .ICDISR1 &= ~(1 << 25); //����58���ж�Ϊ��ȫģʽ
	ICDISER .ICDISER1 = (1 << 25); //��26λ��1 ʹ��58���ж�
	ICDIPR .ICDIPR14 = (ICDIPR .ICDIPR14 & ~(0xff << 8)) | (1 << 8); //���ȼ�����Ϊ 1
	//(0x1 << 16);//(1 << 16);
	ICDIPTR .ICDIPTR14 = (ICDIPTR .ICDIPTR14 & ~(0xff << 8))
			| (0b00000001 << 8);	//���ý��ж��͵�icc0

	ICDDCR = 1;  //���� icd
	CPU0 .ICCICR = 1; //ʹ��icc

//-----------------------------key3-----------------------------------------------------------------

	GPX1 .CON = (GPX1 .CON & ~(0XF << 8)) | (0xf << 8); //���� gpx1_2 Ϊ�ⲿ�ж�ģʽEXT_INT41[2] key3

	EXT_INT41_CON = (EXT_INT41_CON & ~(0xf << 8)) | (0x2 << 8); //�½��ش����ж��¼�

	EXT_INT41_FLTCON0 |= (1 << 23); // �����ж��˲� ʹ�ܣ��˳����ֶ���
	EXT_INT41_FLTCON0 &= ~(1 << 22); //ѡ����ʱ�˲�

	EXT_INT41_MASK &= ~(1 << 2); //ʹ���ж�
	//GPX1_2 EXT_INT41[2]>> XEINT[10] >> SPI:26  ID:58  �C  EINT[10]  External Interrupt

	//1.�ж�ʹ��  2.�жϰ�ȫ   3.�ж����ȼ� 4.�ж�����irq/fiq 5.cpuѡ��

	ICDISR .ICDISR1 &= ~(1 << 26); //����58���ж�Ϊ��ȫģʽ
	ICDISER .ICDISER1 = (1 << 26); //��26λ��1 ʹ��58���ж�
	ICDIPR .ICDIPR14 = (ICDIPR .ICDIPR14 & ~(0xff << 16)) | (1 << 16); //���ȼ�����Ϊ 1
	//(0x1 << 16);//(1 << 16);
	ICDIPTR .ICDIPTR14 = (ICDIPTR .ICDIPTR14 & ~(0xff << 16))
			| (0b00000001 << 16);	//���ý��ж��͵�icc0

	ICDDCR = 1;  //���� icd
	CPU0 .ICCICR = 1; //ʹ��icc
}
