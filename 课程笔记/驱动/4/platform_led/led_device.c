#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>

void fs4412_led_device_release(struct device *dev)
{
	printk("release ok\n");
}

struct resource fs4412_led_restbl[] = {
	[0] = {
		.start = 0x11000c40,
		.end = 0x11000c40 + 4 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = 0x11000c20,
		.end = 0x11000c20 + 4 - 1,
		.flags = IORESOURCE_MEM,
	},
	[2] = {
		.start = 0x114001e0,
		.end = 0x114001e0 + 4 - 1,
		.flags = IORESOURCE_MEM,
	},
};

struct platform_device led_pdev = {
	.name = "led",
	.dev = {
		.release = fs4412_led_device_release,
	},
	.resource = fs4412_led_restbl,
};

int fs4412_led_device_init(void)
{
	platform_device_register(&led_pdev);
	return 0;
}
module_init(fs4412_led_device_init);

void fs4412_led_device_exit(void)
{
	platform_device_unregister(&led_pdev);
	return ;
}
module_exit(fs4412_led_device_exit);
MODULE_LICENSE("GPL");
