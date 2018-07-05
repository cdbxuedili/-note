
objs := start.o system_clock_init.o uart.o uart.o main.o

uart.bin : $(objs)
	arm-none-linux-gnueabi-ld -Tuart.lds -o uart.elf $^
	arm-none-linux-gnueabi-objcopy -O binary -S uart.elf $@
	arm-none-linux-gnueabi-objdump -D -m arm  uart.elf > uart.dis
	cp  uart.bin   /home/linux/Exynos4412/sdfuse
%.o:%.c
	arm-none-linux-gnueabi-gcc -Wall -marm -fno-builtin -c -O2 -o $@ $<

%.o:%.S
	arm-none-linux-gnueabi-gcc -Wall -marm -c -O2 -o $@ $<

clean:
	rm -f  *.dis *.bin *.elf *.o
	
	

