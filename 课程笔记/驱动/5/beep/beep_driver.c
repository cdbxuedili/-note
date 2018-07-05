#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <asm/io.h>
#include "head.h"

int beep_major;
struct class *beep_cls;
struct device *beep_devs;

unsigned int *gpd0con;
void __iomem *beep_base;

int fs4412_beep_open(struct inode *inode,struct file *filp)
{
	//设置定时器输出
	writel((readl(gpd0con) & ~(0xf << 0)) | 2,gpd0con);

	//设置预分频值
	writel((readl(beep_base) & ~(0xff)) | 255,beep_base);

	writel((readl(beep_base + 4) & ~0xf) | 2,beep_base + 4);

	writel(500,beep_base + 0x0c);
	writel(250,beep_base + 0x10);
	
	writel((readl(beep_base + 0x08) & ~(0x1f)) | 2,beep_base + 0x08);
	return 0;
}

long fs4412_beep_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	switch(cmd)
	{
	case BEEP_ON:
		writel((readl(beep_base + 0x08) & ~(0x1f)) | 9,beep_base + 0x08);
		break;
	case BEEP_OFF:
		writel((readl(beep_base + 0x08) & ~(0x1f)),beep_base + 0x08);
		break;
	}
	return 0;
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = fs4412_beep_open,
	.unlocked_ioctl = fs4412_beep_ioctl,

};

int fs4412_beep_probe(struct platform_device *pdev)
{
	printk("match ok\n");
	
	beep_major = register_chrdev(0,"beep",&fops);
	beep_cls = class_create(THIS_MODULE,"beep");
	beep_devs = device_create(beep_cls,NULL,MKDEV(beep_major,0),NULL,"beep");

	gpd0con = ioremap(pdev->resource[0].start,4);
	beep_base = ioremap(pdev->resource[1].start,0x14);
	return 0;
}

int fs4412_beep_remove(struct platform_device *pdev)
{
	device_destroy(beep_cls,MKDEV(beep_major,0));
	class_destroy(beep_cls);
	unregister_chrdev(beep_major,"beep");
	return 0;
}
struct platform_driver beep_drv = {
	.driver = {
		.name = "beep",
	},

	.probe = fs4412_beep_probe,
	.remove = fs4412_beep_remove,
};

module_platform_driver(beep_drv);
MODULE_LICENSE("GPL");
