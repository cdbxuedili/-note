
SHELL= cmd.exe
all:
	arm-none-eabi-gcc -g -c asm.s -o asm.o
	arm-none-eabi-gcc -g -c asm_delay.s -o asm_delay.o
	arm-none-eabi-ld -Ttext 0x40008000 asm.o asm_delay.o -o asm.elf
	arm-none-eabi-objdump -D asm.elf > asm.dis
	
clean:
	rm -rf *.dis *.elf *.o