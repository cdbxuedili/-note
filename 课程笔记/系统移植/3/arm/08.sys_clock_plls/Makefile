led.bin : start.S  led.lds
	arm-none-linux-gnueabi-gcc -c -o start.o start.S
	arm-none-linux-gnueabi-gcc -c -o system_clock_init.o   system_clock_init.c
	arm-none-linux-gnueabi-gcc -c -o led.o led.c
	arm-none-linux-gnueabi-ld -Tled.lds -N led.o  start.o system_clock_init.o  -o led.elf
	arm-none-linux-gnueabi-objcopy -O binary -S led.elf led.bin
	arm-none-linux-gnueabi-objdump -D -m arm  led.elf > led.dis
	cp  led.bin    /home/linux/Exynos4412/sdfuse

clean:
	rm -f *.dis *.bin *.elf *.o

	

