ifeq ($(KERNELRELEASE),)

PWD ?= $(shell pwd)
KERNEL_DIR ?= /home/linux/linux-3.14/
#KERNEL_DIR ?= /lib/modules/3.5.0-23-generic/build 

modules:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
else 
obj-m += platform_fb.o
endif


