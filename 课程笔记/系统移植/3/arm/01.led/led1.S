.text
.globl _start
_start:



	ps  hold
   ldr  r0,=0x1002330c
   ldr r1,[r0]
   orr  r1,r1,#0x300
   str  r1,[r0]

   //disable  
   ldr  r0,=0x11000c08
   ldr  r1,=0x0 
   str  r1,[r0]
	/*WATCHDOG */
   ldr r0,=0x1002040c
   ldr r1,=0x00
   str  r1,[r0]
    /*
     * set GPX1CON as output
     */
    ldr r0, =0x114001e0     // GPX1CON的地址
    ldr r1, [r0]            // 先读出原值
    bic r1, r1, #0xff0000     // 清除bit[23:16]
    orr r1, r1, #0x110000     // 设置bit[23:16]为110000
    str r1, [r0]            // 写入GPX1CON


    /*
     *  set GPX1DAT as HIGH For  leds 
     */
    ldr r0, =0x114001e4  // GPX1DAT的地址
	ldr r1, [r0]         // 读出原值
    
    orr r1, r1, #0x30     // 设置bit[5:4]为3
	str  r1,[r0]
	

   
halt_loop:
    b halt_loop
