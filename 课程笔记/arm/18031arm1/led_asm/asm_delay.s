

.text
.globl asm_delay
asm_delay:

	mov r2,#0xf000000
11:
	subs r2,r2,#1
	bne 11b

	mov pc,lr @bx lr
