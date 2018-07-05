#include<linux/init.h>
#include<linux/module.h>
#include<linux/platform_device.h>

MODULE_LICENSE("GPL");

void pdev_release(struct device *dev)
{
	printk("platform_device release success\n");
}

struct platform_device pdev = {
	.name = "laowu",
	.dev = {
		.release = pdev_release,
	},
	
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
