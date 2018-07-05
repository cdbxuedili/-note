
// GPIO
#define GPA0CON             (*(volatile unsigned int *)0x11400000)
#define GPA1CON             (*(volatile unsigned int *)0x11400020)
// system clock
#define CLK_SRC_PERIL0      (*(volatile unsigned int *)0x1003C250)
#define CLK_DIV_PERIL0      (*(volatile unsigned int *)0x1003C550)
// UART
#define UFCON0              (*(volatile unsigned int *)0x13800008)
#define ULCON0              (*(volatile unsigned int *)0x13800000)
#define UCON0               (*(volatile unsigned int *)0x13800004)
#define UBRDIV0             (*(volatile unsigned int *)0x13800028)
#define UFRACVAL0           (*(volatile unsigned int *)0x1380002c)
#define UTXH0               (*(volatile unsigned int *)0x13800020)
#define URXH0				(*(volatile unsigned int *)0x13800024)

#define UTRSTAT0            (*(volatile unsigned int *)0x13800010)


char getc(void)
{
	char c;
	/* ��ѯ״̬�Ĵ�����ֱ������Ч���� */
	while (!(UTRSTAT0 & (1<<0)));
	
	c = URXH0; /* ��ȡ���ռĴ�����ֵ */
		
	return c;
}

void putc(char c)
{
    /* ��ѯ״̬�Ĵ�����ֱ�����ͻ���Ϊ�� */
    while (!(UTRSTAT0 & (1<<2)));
    
    UTXH0 = c; /* д�뷢�ͼĴ��� */
    
    return;
}

void puts(char *s)
{
    while (*s)
    {
        putc(*s);
        s++;
    }
}

void uart_init(void)
{
    /* 1.������Ӧ��GPIO���ڴ��ڹ��� */
    GPA0CON = 0x22222222;
   // GPA1CON = 0x222222;

    /* 2.����UARTʱ��ԴSCLK_UART */
    /* 2.1 CLK_SRC_DMC  : bit[12]��MUX_MPLL_SEL=1, SCLKMPLLLʹ��MPLL�����
     * 2.2 CLK_SRC_TOP1 : bit[12]��MUX_MPLL_USER_SEL_T=1, MUXMPLLʹ��SCLKMPLLL
     * 2.3 CLK_SRC_PERIL0 : bit[3:0]��UART0_SEL=6, MOUTUART0ʹ��SCLKMPLL_USER_T
     * ����, MOUTUART0������MPLL�����, 800MHz
     */
    /*
     *   PWM_SEL = 0;
     *   UART5_SEL = 0;
     *   UART4_SEL = 6;      // ����ʱ��Դѡ SCLKMPLL_USER_T
     *   UART3_SEL = 6;
     *   UART2_SEL = 6;
     *   UART1_SEL = 6;
     *   UART0_SEL = 6;
     */
    CLK_SRC_PERIL0 = ((0 << 24) | (0 << 20) | (6 << 16) | (6 << 12) | (6<< 8) | (6 << 4)    | (6));

    /*
     �� ��Ƶϵ�� = 7+1 = 8
     * 2.4 CLK_DIV_PERIL0 : bit[3:0]��UART0_RATIO=7,����SCLK_UART0=MOUTUART0/(7+1)=100MHz
     */
    CLK_DIV_PERIL0 = ((7 << 20) | (7 << 16) | (7 << 12) | (7 << 8) | (7 << 4) | (7));

    /* 3.���ô���0��� */
    /* ����FIFO�жϴ�����ֵ
     * ʹ��FIFO
     */
    UFCON0 = 0x111;
    
    /* �������ݸ�ʽ: 8n1, ��8������λ,û�н���λ,1��ֹͣλ */
    ULCON0 = 0x3;
    
    /* �������ж�/��ѯģʽ
     * ��һ����DMAģʽ,���²�ʹ��
     */
    UCON0  = 0x5;
    
    /* SCLK_UART0=100MHz, ����������Ϊ115200
     * �Ĵ�����ֵ���¼���:
     *    DIV_VAL   = 100,000,000 / (115200 * 16)   - 1 = 53.25
     *    UBRDIVn0  = �������� = 53
     *    UFRACVAL0 = С������ x 16 = 0.25 * 16 = 4
     */
    UBRDIV0 = 53;
    UFRACVAL0 = 4;
}
