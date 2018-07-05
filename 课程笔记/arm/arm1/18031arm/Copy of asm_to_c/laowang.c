/*
 6.2.3.198 GPX1CON
   Base Address: 0x1100_0000
   Address = Base Address + 0x0C20, Reset Value = 0x0000_0000
 Name  Bit  Type  Description  Reset Value
 GPX1CON[7]  [31:28]  RW
 0x0 = Input
 0x1 = Output
 0x2 = Reserved
 0x3 = KP_COL[7]
 0x4 = Reserved
 0x5 = ALV_DBG[11]
 0x6 to 0xE = Reserved
 0xF = WAKEUP_INT1[7]

 */


void laowu();

long long  fun(int a,int b,int c,int d,int n,int m)
{
	a = a + 1;

	return 0x1234567888888888LL;
}


void led() {
	unsigned int *p;
	p = (unsigned int *) (0x11000000 + 0x0C20);
	*p = (*p & 0xfffffff0) | 0x00000001;

	p = (unsigned int *) (0x11000000 + 0x0C24);

	while (1) {
		*p |= 0b00000001;

		asm_delay();  // 最终 会被编程成 bl asm_delay

		*p &= ~0b00000001;
		asm_delay();
	}

	while (1)
		;
	return;
}

void laoli(int *x) {
	int a,b,c,d;
	a = 251;

	a  = 0x12345678; // 0x78123456

	a = asm_ror(a);

	int i = 1 <<30;
	while(i --);
	i = -1;


	asm volatile  (
			"mov %0,%2,ror #8\n"   // a= b ror 8
			"mov r4,r5\n"
			"ldr %0,%3\n"		   // b = d
			"str %0,%1\n"		   // c = b

			"ldr r4,%3\n"		// r4 = d
			"str r4,%1\n"		// c = r4


			:"+r"(b),"=m"(c)/*输出列表：从汇编到c传值  r:通过寄存器传递 m:内存传递
			 	 	 	 	 	 	 			+:可读写   =：只写*/
			:"r"(a),"m"(d)  /*输入列表：c到汇编 */
			:"r4"/*易变列表*/

	);

	asm volatile ("mov r0,#250\n");
	__asm__ __volatile__ ("mov r0,#250\n");
	asm(
			"mov %0,%0,ror #8\n"
			"mov r4,#123\n"
			:"+r"(a)
			:
			:"r4"
	);
	asm(
			"mov r0,#250\n"
			:
			:
			:"r0"

	);





	//asm("swi #250\n");


	asm_delay(0xf00000);
	a = fun(123,124,125,126,250,251);



	led();
	laowu();

	return;
}
void laowu() {
	int b;
	b = 250;
}

