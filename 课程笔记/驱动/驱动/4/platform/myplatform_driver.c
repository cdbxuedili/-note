#include<linux/module.h>
#include<linux/init.h>
#include<linux/platform_device.h>

MODULE_LICENSE("GPL");

int mypalt_drv_probe(struct platform_device *pdev)//一旦匹配成功,dev指针会被struct platform_device结构首地址赋值
{

	printk("laowu he laomeng match ok?\n");
	return 0;
}
int mypalt_drv_remove(struct platform_device *pdev)
{
	printk("remove success\n");
	return 0;
}

struct platform_driver pdrv = {
	.driver = {
		.name = "laowu",
	},
	.probe = mypalt_drv_probe,
	.remove = mypalt_drv_remove,
};

int plat_drv_init(void)
{
	platform_driver_register(&pdrv);
	printk("platform_driver init success\n");
	return 0;
}

module_init(plat_drv_init);

void plat_drv_exit(void)
{
	platform_driver_unregister(&pdrv);
	printk("platform_driver exit success\n");
	return;
}

module_exit(plat_drv_exit);

