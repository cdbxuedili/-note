#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

void fs4412_beep_dev_release(struct device *dev)
{

}

struct resource fs4412_beep_dev_restbl[] = {
	{
		.start = 0x114000a0,
		.end = 0x114000a0 + 4 - 1,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = 0x139d0000,
		.end = 0x139d0000 + 0x10 + 4 - 1,
		.flags = IORESOURCE_MEM,
	},
};

struct platform_device beep_dev = {
	.name = "beep",
	.dev = {
		.release = fs4412_beep_dev_release,
	},

	.resource = fs4412_beep_dev_restbl,

};

int fs4412_beep_dev_init(void)
{
	platform_device_register(&beep_dev);
	return 0;
}
module_init(fs4412_beep_dev_init);

void fs4412_beep_dev_exit(void)
{
	platform_device_unregister(&beep_dev);
	return;
}
module_exit(fs4412_beep_dev_exit);
MODULE_LICENSE("GPL");
