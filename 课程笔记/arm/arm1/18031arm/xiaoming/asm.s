


.text
.globl _start
_start:
	nop


	ldr r0,=fun

	mov r9,#123
	adrl r0,fun

	mov r9,#123
	adr r1,_start


	ldmia sp!,{r0-r5}
	ldmfd sp!,{r0-r5}
	ldmfd sp,{r0-r5}

	ldr r0,=0x40008000
1:
	ldr r1,=0x41000000
1:
	ldm r0,{r1,r6,r3}

	b 1b

88:
	ldm r0!,{r2-r11}
1:
	stm r1!,{r2-r11}
	b 88b
1:
	#while(i--);
	mov r5,#40
88:
	ldr r2,[r0],#4
	str r2,[r1],#4

	subs r5,r5,#1
	bne 88b


	ldrsb r2,data




	ldr r0,c
	ldrh r0,c
	ldrb r0,c

	ldr r0,a
	ldr r1,b

	add r0,r0,r1

	str r0,a

_stop:
	b _stop

a:
	.word 10
b:
	.word 20

c:
	.word 0xffffffff
data:
	.byte -1
	.byte -1
	.byte -1
	.byte -1
.space 1024 + 888

fun:

	mov r0,#250
	nop

	bx lr  @mov pc,lr

str:
.string "123"




