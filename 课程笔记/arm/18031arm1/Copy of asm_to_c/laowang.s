	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"laowang.c"
	.text
	.align	2
	.global	laowu
	.type	laowu, %function
laowu:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, #250
	str	r3, [fp, #-8]
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	laowu, .-laowu
	.align	2
	.global	laoli
	.type	laoli, %function
laoli:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	mov	r3, #251
	str	r3, [fp, #-8]
	bl	laowu
	sub	sp, fp, #4
	ldmfd	sp!, {fp, lr}
	bx	lr
	.size	laoli, .-laoli
	.ident	"GCC: (GNU) 4.6.2"
