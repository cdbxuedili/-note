.text
.globl _start
_start:


    
    ldr sp, =0x02027800 // 调用C函数之前必须设置栈,栈用于保存运行环境,给局部变量分配空间
                        // 参考ROM手册P14, 我们把栈指向BL2上方1K处(1K已经够用),
                        // 即:0x02020000 (iRAM基地址) + 5K(iROM代码用) + 8K(BL1用) + 16K(BL2用) + 1K(用作栈))
    
	bl  ps_hold_on

    bl main             // 调用main函数
halt_loop:
    b halt_loop

ps_hold_on:


	/*gpx0_2   ono*/
	ldr	r0, =0x11000C00

	ldr	r1, [r0]
	bic	r1, #0xF00
	orr	r1, #0x100
	str	r1, [r0]

	ldr	r1, [r0, #4]
	orr	r1, r1, #4
	str	r1, [r0, #4]

	ldr	r0, =0x1002330C
	ldr	r1, [r0]
	orr	r1, r1, #0x300
	str	r1, [r0]
	mov	pc, lr
