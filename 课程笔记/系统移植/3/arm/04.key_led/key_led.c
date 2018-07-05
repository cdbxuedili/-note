
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
     * 配置GPX1_0,GPF3_4,GPF3_5为输出引脚
    
     */
    GPF3CON = 0x11 << 16;

    /* 设置K1、K2为输入 */
    GPX1CON = (0x00 << 4)  ;
        
    while (1)
    {
        val = GPX1DAT;           /* 读出按键引脚状态 */
        
            if (val & (1<<1)) /* 某个按键是松开状态 : 高电平 */
            {
                /* 熄灭对应LED*/
                GPF3DAT &= ~(1 << 4);
            }   
            else
            {
                /* 否则点亮对应LED */
                GPF3DAT |=(1<< 4);
               
            }
        }

    return 0;
}
