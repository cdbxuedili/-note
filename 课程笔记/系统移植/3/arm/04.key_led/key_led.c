
#define GPX1CON     (*(volatile unsigned int *)0x11000C20)
#define GPX1DAT     (*(volatile unsigned int *)0x11000C24)

#define GPF3CON     (*(volatile unsigned int *)0x114001E0)
#define GPF3DAT     (*(volatile unsigned int *)0x114001E4)
#define GPX1CON     (*(volatile unsigned int *)0x11000C20)
#define GPX1DAT     (*(volatile unsigned int *)0x11000C24)

int main(void)
{
    int val;
    
    /*
     * ����GPX1_0,GPF3_4,GPF3_5Ϊ�������
    
     */
    GPF3CON = 0x11 << 16;

    /* ����K1��K2Ϊ���� */
    GPX1CON = (0x00 << 4)  ;
        
    while (1)
    {
        val = GPX1DAT;           /* ������������״̬ */
        
            if (val & (1<<1)) /* ĳ���������ɿ�״̬ : �ߵ�ƽ */
            {
                /* Ϩ���ӦLED*/
                GPF3DAT &= ~(1 << 4);
            }   
            else
            {
                /* ���������ӦLED */
                GPF3DAT |=(1<< 4);
               
            }
        }

    return 0;
}
