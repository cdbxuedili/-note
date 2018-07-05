#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>

int demo_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
	printk("match ok\n");
	return 0;
}
int demo_remove(struct i2c_client *client)
{
	return 0;
}

struct of_device_id demo_tbl[] = {
	{
		.compatible = "fs4412,mpu6050",
	},
	{},
};

struct i2c_device_id demo_id_tbl[] = {
	{
		.name = "18031",//name必须要有内容,但是内容是什么不重要(前提是和设备树匹配)
	},
};

struct i2c_driver drv = {
	.driver = {
		.name = "demo", //   /sys/bus/i2c/demo
		.of_match_table = demo_tbl,
	},	

	.probe = demo_probe,
	.remove = demo_remove,

	.id_table = demo_id_tbl,
};

#if 0
int __init demo_init(void)
{
	i2c_add_driver(&drv);
	return 0;
}
module_init(demo_init);

void __exit demo_exit(void)
{
	i2c_del_driver(&drv);
	return;
}
module_exit(demo_exit);
#endif

module_i2c_driver(drv);
MODULE_LICENSE("GPL");
