#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

void fs4412_platdev_release(struct device *dev)
{
	printk("release success\n");
}

struct platform_device pdev = {
	.name = "18031",
	.dev = {
		.release = fs4412_platdev_release,
	},
};

int fs4412_platdev_init(void)
{
	platform_device_register(&pdev);
	return 0;
}
module_init(fs4412_platdev_init);

void fs4412_platdev_exit(void)
{
	platform_device_unregister(&pdev);
	return;
}
module_exit(fs4412_platdev_exit);
MODULE_LICENSE("GPL");
