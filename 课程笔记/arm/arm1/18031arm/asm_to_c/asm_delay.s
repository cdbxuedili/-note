

.text
.globl asm_delay
asm_delay:

	stmfd sp!,{r4} @ѹվ����
	mov r4,r0 		@���մ���
11:
	subs r4,r4,#1
	bne 11b

	ldmfd sp!,{r4} @��ջ��ԭ

	mov r0,#0 	@��д����ֵΪ0

	mov pc,lr @bx lr

.globl asm_ror
asm_ror:

	mov r0,r0,ror #8

	bx lr




