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

void fun(int a)
{
	a = a + 1;
	return ;
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

void laoli() {
	int a;
	a = 251;

	fun(123);

	asm_delay(0xf00000);

	led();
	laowu();

	return;
}
void laowu() {
	int b;
	b = 250;
}

