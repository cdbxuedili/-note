

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


.text
.globl _start
_start:
	nop
/*
	ldr r0,a
	bic r0,r0,#0x000000ff
	str r0,a
*/
	ldr r0,=0x11000c20			@准备地址
	ldr r1,[r0]					@读取片上外设寄存器值到cpu
	bic r1,r1,#0x0000000f		@对应位清零
	orr r1,r1,#0x00000001		@设置对应值
	str r1,[r0]					@写回到片上外设 寄存器


23:
	ldr r0,=0x11000c24
	ldr r1,[r0]
	orr r1,r1,#0b00000001
	str r1,[r0]

	mov r2,#0xf000000
11:
	subs r2,r2,#1
	bne 11b

	ldr r0,=0x11000c24
	ldr r1,[r0]
	and r1,r1,#0b11111110 @bic r1,r1,#0b00000001
	str r1,[r0]

# delay
	mov r2,#0xf000000
11:
	subs r2,r2,#1
	bne 11b

	b 23b








_stop:
	b _stop


a:
	.word



