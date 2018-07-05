
SHELL= cmd.exe
all:
	arm-none-eabi-gcc -g -c asm.s -o asm.o
	arm-none-eabi-ld -Ttext 0x40008000 asm.o -o asm.elf
	arm-none-eabi-objdump -D asm.elf > asm.dis