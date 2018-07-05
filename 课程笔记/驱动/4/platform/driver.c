#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>

int fs4412_platdrv_probe(struct platform_device *pdev)
{
	printk("match ok\n");
	return 0;
}

int fs4412_platdrv_remove(struct platform_device *pdev)
{
	printk("remove ok\n");
	return 0;
}
struct platform_driver pdrv = {
	.driver = {
		.name = "18031", 
	},
	.probe = fs4412_platdrv_probe,
	.remove = fs4412_platdrv_remove,
};

int fs4412_platdrv_init(void)
{
	platform_driver_register(&pdrv);
	return 0;
}
module_init(fs4412_platdrv_init);

void fs4412_platdrv_exit(void)
{
	platform_driver_unregister(&pdrv);
	return ;
}
module_exit(fs4412_platdrv_exit);
MODULE_LICENSE("GPL");
