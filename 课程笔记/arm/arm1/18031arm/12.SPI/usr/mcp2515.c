#include "mcp2515.h"
#include "exynos_4412.h"

void delay(int times)
{
	volatile int i,j;
	for (j = 0; j < times; j++)
	{
		for (i = 0; i < 1000; i++);
	}
}
/*
 * Ƭѡ�ӻ�
 */
void slave_enable(void)
{

	SPI2.CS_REG &= ~0x1; //enable salve
	delay(3);
}
/*
 * ȡ��Ƭѡ�ӻ�
 */
void slave_disable(void)
{

	SPI2.CS_REG |= 0x1; //disable salve
	delay(1);
}
/*
 * ���ܣ���SPI���߷���һ���ֽ�
 */
void send_byte(unsigned char data)
{
	SPI2.CH_CFG |= 0x1; // enable Tx Channel
	delay(1);
	SPI2.SPI_TX_DATA = data;
	while( !(SPI2.SPI_STATUS & (0x1 << 25)) );
	SPI2.CH_CFG &= ~0x1; // disable Tx Channel
}
/*
 * ���ܣ���SPI���߶�ȡһ���ֽ�
 */
unsigned char recv_byte()
{
	unsigned char data;
	SPI2.CH_CFG |= 0x1 << 1; // enable Rx Channel
	delay(1);
	data = SPI2.SPI_RX_DATA;
	delay(1);
	SPI2.CH_CFG &= ~(0x1 << 1); //disable Rx Channel
	return  data;
}
/*
 * ��λspi������
 */
void soft_reset(void)
{
	SPI2.CH_CFG |= 0x1 << 5;
	delay(1);                     //��ʱ
	SPI2.CH_CFG &= ~(0x1 << 5);
}

//���ܣ���λָ��������³�ʼ��MCP2515 ���ڲ��Ĵ���������������ģʽ
void reset_2515()
{
	soft_reset();      //��λspi������
    slave_enable() ;   //Ƭѡ�ӻ�
	send_byte(0xc0);   //���͸�λ����
	slave_disable() ;  //ȡ��Ƭѡ

}
//���ܣ�����������
void send_req_2515()
{
 //   CS_SPI = 0; //��λ
	soft_reset();      //��λspi������
    slave_enable() ;   //Ƭѡ�ӻ�
	send_byte(0x81);   //������������
	slave_disable() ;  //ȡ��Ƭѡ
//	CS_SPI=1;
}
//���ܣ�ֻ�޸ļĴ����е�ĳЩλ
//��ڲ�����Addr:�ķ�����ַ  MASK��������  Ϊ1ʱ���ԶԵ�ǰλ�޸�  dat:�����ֽ�
void bit_modify_2515(unsigned char addr, unsigned char mask, unsigned char data)
{
//    CS_SPI = 0 ;
    slave_enable() ;
    send_byte(0x05) ;
    send_byte(addr) ;
    send_byte(mask) ;
    send_byte(data) ;
    slave_disable() ;
//    CS_SPI = 1 ;
}

/*
 * ���ܣ���ָ����ַ��ʼ�ļĴ�����ȡ���ݡ�
 *unsigned char Addr Ҫ��ȡ��ַ�Ĵ����ĵ�ַ
 *����ֵ���ӵ�ַ���ж�ȡ����ֵ
 */
unsigned char read_byte_2515(unsigned char Addr)
{
	unsigned char ret;
//    CS_SPI = 0;
    slave_enable();
    send_byte(0x03);
    send_byte(Addr);
    ret = recv_byte();
    slave_disable();
//    CS_SPI = 1;
    return(ret);
}

/*
 * ���ܣ�������д��ָ����ַ��ʼ�ļĴ�����
 * unsigned char addr �Ĵ����ĵ�ַ
 * unsigned char data ��Ĵ���д�������
 */
void write_byte_2515(unsigned char addr,unsigned char data)
{
    slave_enable();
    send_byte(0x02);
    send_byte(addr);
    send_byte(data);
    slave_disable();
}

void  Init_can(void)
{
//unsigned char ret;
    reset_2515(); //��λ
    write_byte_2515(0x0f, 0x80);     //CANCTRL�Ĵ���������������ģʽ ����DATASHEET 58ҳ

	//�������õĲ����� 5K 10K 15K 20K 25K 40K 50K 80K 100K 125K 200K 400K 500K 667K 800K 1M
    write_byte_2515(0x2A, CNF1_20K); //CNF1λ��ʱ���ü���   ����DATASHEET 41-42ҳ
    write_byte_2515(0x29, CNF2_20K); //CNF2λ��ʱ���ü���   ����DATASHEET 41-42ҳ
    write_byte_2515(0x28, CNF3_20K); //CNF3λ��ʱ���ü���   ����DATASHEET 41-43ҳ
    write_byte_2515(0x2B, 0x1f);     //CANINTE�ж�ʹ�ܼĴ���  ����DATASHEET 50 ҳ
    write_byte_2515(0x60, 0x60);     //RXB0CTRL���ջ�����0 ���ƼĴ��� ����DATASHEET 27 ҳ
    //write_byte_2515(0x70, 0x20);   //���ջ�����1���ƼĴ���
    bit_modify_2515(0x0C, 0x0f, 0x0f); //BFPCTRL_RXnBF ���ſ��ƼĴ�����״̬�Ĵ��� ����DATASHEET 29 ҳ

    write_byte_2515(0x0f, 0x40);   //CAN���ƼĴ��������ػ�ģʽ,���ڲ���
}

/*
 * tx_buff[]
 * Fream ����֡������
 */
void Can_send(unsigned char *tx_buff)
{
	unsigned char i;
	write_byte_2515(0x30, 0x03); //����Ϊ����������ȼ�
	write_byte_2515(0x31, 0xff); //���ͻ�����0��׼��ʶ����λ
	write_byte_2515(0x32, 0x00); //���ͻ�����0��׼��ʶ����λ
	write_byte_2515(0x35, 0x08);  //���ͻ�����0���ݳ�����8�ֽ�
	for(i = 0; i < 8; i++)
	{
		write_byte_2515(0x36+i ,tx_buff[i]); //��txb��������д��8���ֽ�
//		printf("%x ",tx_buff[i]);
	}
	send_req_2515();

}

unsigned char Can_receive(unsigned char *rx_buff)
{
	unsigned char i,flag;
    flag = read_byte_2515(0x2c); //CANINTF�����жϱ�־�Ĵ���
    printf("flag=%x\n",flag);
  //  printf(" SPI2.SPI_STATUS =%x\n", SPI2.SPI_STATUS );
 //   soft_reset();
    if (flag&0x1)                //���ջ�����0���жϱ�־λ
    {
    	for(i = 0; i < 16; i++)
		{
    		rx_buff[i]= read_byte_2515(0x60+i);
    //		printf("%x ",rx_buff[i]);
    //		printf(" SPI2.SPI_STATUS =%x\n", SPI2.SPI_STATUS );
    		soft_reset();
		}
    	bit_modify_2515(0x2c,0x01,0x00);
    	write_byte_2515(0x2c, 0x00);
		if (!(rx_buff[1]&0x08)) return(1);	  //���ձ�׼����֡
    }
    return(0);
}

