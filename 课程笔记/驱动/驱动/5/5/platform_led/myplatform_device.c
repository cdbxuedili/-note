#include<linux/init.h>
#include<linux/module.h>
#include<linux/platform_device.h>

MODULE_LICENSE("GPL");

void pdev_release(struct device *dev)
{
	printk("platform_device release success\n");
}

struct resource resource_tbl[] = {
	{
		.start = 0x11000c40,
		.end = 0x11000c40+0x4,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = 0x11000c20,
		.end = 0x11000c20+0x4,
		.flags = IORESOURCE_MEM,
	
	},
	{
		.start = 0x114001e0,
		.end = 0x114001e0+0x4,
		.flags = IORESOURCE_MEM,
	},
};

struct platform_device pdev = {
//	.name = "laowu",
	.name = "abc",
	.dev = {
		.release = pdev_release,
	},

	.resource = resource_tbl,
};

int myplat_dev_init(void)
{
	platform_device_register(&pdev);
	printk("init success\n");
	return 0;
}

module_init(myplat_dev_init);

void myplat_dev_exit(void)
{
	platform_device_unregister(&pdev);
	printk("exit success\n");
	return ;
}

module_exit(myplat_dev_exit);
