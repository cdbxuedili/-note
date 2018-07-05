

.text
.globl _start
_start:
	nop

start:

	cmp r0,r1
	beq stop

#	cmp r0,r1

	subgt r0,r0,r1
	suble r1,r1,r0

	b start
stop:



_stop:
	b _stop

