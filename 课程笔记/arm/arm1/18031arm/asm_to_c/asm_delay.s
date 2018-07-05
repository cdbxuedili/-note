

.text
.globl asm_delay
asm_delay:

	stmfd sp!,{r4} @压站保护
	mov r4,r0 		@接收传参
11:
	subs r4,r4,#1
	bne 11b

	ldmfd sp!,{r4} @出栈还原

	mov r0,#0 	@填写返回值为0

	mov pc,lr @bx lr

.globl asm_ror
asm_ror:

	mov r0,r0,ror #8

	bx lr




