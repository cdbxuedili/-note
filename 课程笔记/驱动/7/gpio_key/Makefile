ifeq ($(KERNELRELEASE),)
PWD = $(shell pwd)

#当你需要让驱动在开发板上验证时使用
KERNEL_DIR = /home/linux/linux-3.14/

#当你需要让驱动在x86上验证时使用
#KERNEL_DIR = /lib/modules/$(shell uname -r)/build

#start:
modules:
	#cd ~/linux-3.14/ 
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
else
obj-m += gpio_key.o
endif
