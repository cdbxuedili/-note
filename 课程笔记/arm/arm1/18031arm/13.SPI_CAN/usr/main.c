/*
 *@brief	This example describes how to use SPI--CAN
 *@date:	12. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"
#include "uart.h"


unsigned char src[]="1234567" ;
unsigned char dst[20]={0};

/*
 * Irq_rutine
 * */
void do_irq() {

}

/**********************************************************************
 * @brief		mydelay_ms_ms_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void mydelay_ms(int time)
{
	int i, j;
	while(time--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}


/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void)
{
	GPX2.CON = 0x1 << 28;
	uart_init();

	unsigned char ID[4],buff[8];            					//״̬��
	unsigned char key;
	unsigned char ret;//,j,k,ret0,ret1,ret2,ret3,ret4,ret5,ret6,ret7,ret8,ret9;
	unsigned int rx_counter;
	volatile int i=0;

	GPC1.CON = (GPC1.CON & ~0xffff0) | 0x55550;//����IO����ΪSPIģʽ

/*spi clock config*/
	CLK_SRC_PERIL1 = (CLK_SRC_PERIL1 & ~(0xF<<24)) | 6<<24;// 0x6: 0110 = SCLKMPLL_USER_T 800Mhz
	CLK_DIV_PERIL2 = 19 <<8 | 3;//SPI_CLK = 800/(19+1)/(3+1)

	soft_reset();	                   // ��λSPI������
	SPI2.CH_CFG &= ~( (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | 0x3);//master mode, CPOL = 0, CPHA = 0 (Format A)
	SPI2.MODE_CFG &= ~((0x3 << 17) | (0x3 << 29));   //BUS_WIDTH=8bit,CH_WIDTH=8bit
	SPI2.CS_REG &= ~(0x1 << 1);        //ѡ���ֶ�ѡ��оƬ
	mydelay_ms(10);    //��ʱ
    Init_can();   //��ʼ��MCP2515

    printf("\n************ SPI CAN test!! ************\n");

    while(1)
    {
		//Turn on
		GPX2.DAT = GPX2.DAT | 0x1 << 7;
		mydelay_ms(50);

    	printf("\nplease input 8 bytes\n");

    	for(i=0;i<8;i++)
    	{
    		src[i] = getchar();
    		putc(src[i]);
    	}
    	printf("\n");

    	Can_send(src); //���ͱ�׼֡
        mydelay_ms(100);
        ret = Can_receive(dst); //����CAN��������
        printf("ret=%x\n",ret);
        printf("src=");
        for(i=0;i<8;i++) printf(" %x", src[i]);//��CAN�������յ������ݷ������п�

        printf("\n");

        printf("dst=");
        for(i=0;i<8;i++) printf(" %x",dst[6+i]); //��CAN�������յ������ݷ������п�
		printf("\n");

		//Turn off
		GPX2.DAT = GPX2.DAT & ~(0x1 << 7);
		mydelay_ms(100);
    } //while(1)

	return 0;
} //main
