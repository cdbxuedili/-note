

.text
.globl _start
_start:
	nop

	ldr r0,	  =0xaafaaaaa
	bic r0,r0,#0x0fa00000

	ldr r1,=0xffff0000
	bic r0,r0,r1


	#	mov r0,#0x123456

	ADD R0,R1,#0XAFFFFFFE
#	ADD R0,R1,#0XFFFF00FF

	@MOV R0,#0x8000012

	ldr r0,a   @ R0 = *a

	ldr r9,=a  @ r9 = a

	ldr r1,=0x12345678
	ldr r2,=0x120000
	ldr r5,=1234



/*	1200000 12 e 5
	A * 2^N  >> A << N  A ROR (32 - N)

	A ROR (M * 2)

*/
	mov r0,#0xf000000f  @ 0xff ror 4

	mov r0,#250
#	mov r1,#1234
	mov r2,#0x01200000   @0X12 << 20  0X12 ROR 12 0X12 ROR 6 * 2
#	mov r3,#0x1234560
	MOV R4,#0X00001200		@0X12 << 8  0X12 ROR 24	 0X12 ROR 12 * 2

#	MOV R5,#0X1EF00
		    #0..0 0001 1110 1111 0000 0000
	MOV R6,#0X1E800
			#0..0 0001 1110 1000 0000 0000
			#		 11 11010
	MOV R7,#0XFF000
			#1111 1111 0000 0000 0000
	MOV R7,#0X3FC00
			#0011 1111 1100 0000 0000
#	MOV R7,#0X1AE00
			#0001 1010 1110 0000 0000


	add r0,r1,#0x120000
#	add r0,r1,#0xffff00ff

	mov r8,#0xffff00ff


	nop
_stop:
	b _stop

a:
	.word 0x123456


#.space 1024 * 1024 * 33

aaa:

	nop
