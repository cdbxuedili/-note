
#define GPX2CON		(*(volatile unsigned int *)0x11000C40)
#define GPX2DAT		(*(volatile unsigned int *)0x11000C44)
#define GPX1CON		(*(volatile unsigned int *)0x11000C20)
#define GPX1DAT		(*(volatile unsigned int *)0x11000C24)

#define GPF3CON		(*(volatile unsigned int *)0x114001E0)
#define GPF3DAT		(*(volatile unsigned int *)0x114001E4)

void  mydelay()
{

	volatile  int  i   =  0x10;
	//volatile  int  i   =  0x10000;// led  off
	while(i --);

}
int main(void)
{
	unsigned long tmp = 0;

	/*
	 * set GPX1_0 as output
	 */
	tmp = GPX1CON;
	tmp &= ~0xf;
	tmp |= 1;
	GPX1CON = tmp;
	
	/* GPx1_0 output HIGH */
	GPX1DAT |= 1;
	/*
	 *set  GPX2CON  as  output
	 * */

	tmp  = GPX2CON;
	tmp  &= ~(0xf<<28);
	tmp  = (0x1 << 28);
	GPX2CON = tmp;
	/*GPX2_7  output  high*/

	GPX2DAT  = (0x1 <<7);

	tmp  = GPF3CON;
	tmp  &= ~(0xff<<16);
	tmp  = (0x11 << 16);
	GPF3CON = tmp;
	/*GPf3_4  output  high*/

	GPF3DAT  = (0x3 <<4);

	GPX1DAT |= 1;
	GPX2DAT  = (0x1 <<7);
	GPF3DAT  = (0x3 <<4);
#if  0
	while(1)
	{
	

	GPX1DAT &= ~1;
	GPX2DAT  &= ~(0x1 <<7);
	GPF3DAT  &=~ (0x3 <<4);

	mydelay();
	GPX1DAT |= 1;
	GPX2DAT  = (0x1 <<7);
	GPF3DAT  = (0x3 <<4);
	mydelay();
	
	
	}
#endif  

	return 0;
}
