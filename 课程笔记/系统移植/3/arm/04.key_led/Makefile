objs := start.o key_led.o

key_led.bin : $(objs)
	arm-none-linux-gnueabi-ld -Tkey_led.lds -o key_led.elf $^
	arm-none-linux-gnueabi-objcopy -O binary -S key_led.elf $@
	arm-none-linux-gnueabi-objdump -D -m arm  key_led.elf > key_led.dis 
	sudo  cp  key_led.bin   /home/linux/Exynos4412/sdfuse/

%.o:%.c
	arm-none-linux-gnueabi-gcc -Wall -marm -c -O2 -o $@ $<

%.o:%.S
	arm-none-linux-gnueabi-gcc -Wall -marm -c -O2 -o $@ $<

clean:
	rm -f  *.dis *.bin *.elf *.o
	
