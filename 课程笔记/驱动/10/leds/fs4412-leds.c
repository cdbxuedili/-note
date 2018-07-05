#include<linux/init.h>
#include<linux/module.h>
#include<linux/slab.h>
#include<linux/leds.h>
#include<asm/io.h>

volatile unsigned int *gpx2con;
volatile unsigned int *gpx2dat;

static struct led_classdev *fs4412_led_cdev;

void fs4412_brightness_set(struct led_classdev *led_cdev,enum led_brightness brightness)
{
	if(brightness == LED_OFF)
		writel(readl(gpx2dat) & ~(1 << 7),gpx2dat);
	else 
		writel((readl(gpx2dat) & ~(1 << 7)) | 1 << 7,gpx2dat);
}

int fs4412_leds_init(void)
{
	fs4412_led_cdev = kzalloc(sizeof(struct led_classdev),GFP_KERNEL);

	fs4412_led_cdev->name = "led1";// /sys/class/leds/led1目录
	fs4412_led_cdev->brightness = 0;
	fs4412_led_cdev->max_brightness = 255;
	fs4412_led_cdev->flags = LED_CORE_SUSPENDRESUME;
	fs4412_led_cdev->brightness_set = fs4412_brightness_set;
//	fs4412_led_cdev->default_trigger = "timer";

	led_classdev_register(NULL,fs4412_led_cdev);

	gpx2con = ioremap(0x11000c40,0x4);
	gpx2dat = gpx2con + 1;

	writel((readl(gpx2con) & ~(0xf << 28)) | 0x1 << 28,gpx2con);
	writel(readl(gpx2dat) & ~(1 << 7),gpx2dat);
	return 0;
}
module_init(fs4412_leds_init);

void fs4412_leds_exit(void)
{
	iounmap(gpx2con);
	kfree(fs4412_led_cdev);
	led_classdev_unregister(fs4412_led_cdev);
	return;
}
module_exit(fs4412_leds_exit);
MODULE_LICENSE("GPL");
