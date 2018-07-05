#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/io.h>

unsigned int *gpx2con;
unsigned int *gpx2dat;
unsigned int *gpx1con;
unsigned int *gpx1dat;
unsigned int *gpf3con;
unsigned int *gpf3dat;

int led_major;
struct class *led_cls;
struct device *led_devs;

int fs4412_led_driver_open(struct inode *inode,struct file *filp)
{
	writel((readl(gpx2dat) & ~(1 << 7)) | 1 << 7,gpx2dat);
	writel((readl(gpx1dat) & ~(1 << 0)) | 1 << 0,gpx1dat);
	writel((readl(gpf3dat) & ~(1 << 4)) | 1 << 4,gpf3dat);
	writel((readl(gpf3dat) & ~(1 << 5)) | 1 << 5,gpf3dat);
	return 0;
}

int fs4412_led_driver_close(struct inode *inode,struct file *filp)
{
	writel((readl(gpx2dat) & ~(1 << 7)),gpx2dat);
	writel((readl(gpx1dat) & ~(1 << 0)),gpx1dat);
	writel((readl(gpf3dat) & ~(1 << 4)),gpf3dat);
	writel((readl(gpf3dat) & ~(1 << 5)),gpf3dat);
	return 0;
}
struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = fs4412_led_driver_open,
	.release = fs4412_led_driver_close,
};
int fs4412_led_driver_probe(struct platform_device *pdev)//pdev接受的就是led_device.c中的led_pdev首地址
{
	led_major = register_chrdev(0,"led",&fops);
	led_cls = class_create(THIS_MODULE,"led");
	led_devs = device_create(led_cls,NULL,MKDEV(led_major,0),NULL,"led");

	//pdev->resource就是led_device.c中的fs4412_led_restbl
	gpx2con = ioremap(pdev->resource[0].start,4);
	gpx2dat = gpx2con + 1;

	gpx1con = ioremap(pdev->resource[1].start,4);
	gpx1dat = gpx1con + 1;

	gpf3con = ioremap(pdev->resource[2].start,4);
	gpf3dat = gpf3con + 1;

	//设置输出引脚
	writel((readl(gpx2con) & ~(0xf << 28)) | 1 << 28,gpx2con);
	writel((readl(gpx1con) & ~(0xf << 0)) | 1 << 0,gpx1con);
	writel((readl(gpf3con) & ~(0xff << 16)) | 0x11 << 16,gpf3con);
	printk("match ok\n");
	return 0;
}

int fs4412_led_driver_remove(struct platform_device *pdev)
{
	device_destroy(led_cls,MKDEV(led_major,0));
	class_destroy(led_cls);
	unregister_chrdev(led_major,"led");
	return 0;
}

struct of_device_id fs4412_led_driver_tbl[] = {
	{
		.compatible = "fs4412,led",
	},
	{},//这句话如果不加则加载时会出现段错误
};

struct platform_driver led_drv = {
	.driver = {
		.name = "led",
		.of_match_table = fs4412_led_driver_tbl,
	},
	

	.probe = fs4412_led_driver_probe,
	.remove = fs4412_led_driver_remove,
};

#if 0
int fs4412_led_driver_init(void)
{
	platform_driver_register(&led_drv);
	return 0;
}

module_init(fs4412_led_driver_init);

void fs4412_led_driver_exit(void)
{
	platform_driver_unregister(&led_drv);
	return ;
}
module_exit(fs4412_led_driver_exit);
#endif
module_platform_driver(led_drv);
MODULE_LICENSE("GPL");
