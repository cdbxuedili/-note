#include <linux/module.h>
#include <asm/io.h>

#define GPX2CON 0x11000c40

unsigned int *gpx2con;
unsigned int *gpx2dat;

//void __iomem *gpx2con;

MODULE_LICENSE("GPL");


static int __init led_init(void)  //自定义加载函数
{
	gpx2con = ioremap(GPX2CON,4);//返回值就是寄存器的对应虚拟地址	
	gpx2dat = gpx2con + 1;//数据寄存器的虚拟地址

//	*gpx2con = (*gpx2con & ~(0xf << 28)) | 1 << 28;//设置输出引脚
//	*gpx2dat = (*gpx2dat & ~(1 << 7)) | 1 << 7;//点亮led2

	writel(  (readl(gpx2con) & ~(0xf << 28)) | 1 << 28 , gpx2con);
	writel((readl(gpx2dat) & ~(1 << 7)) | 1 << 7,gpx2dat);

	return 0;
}

module_init(led_init);//将自定义加载函数和默认加载函数绑定

static void __exit led_exit(void)
{
//	*gpx2dat = (*gpx2dat & ~(1 << 7));//点亮led2
	writel(readl(gpx2dat) & ~(1 << 7),gpx2dat);
	iounmap(gpx2con);
	return;
}
module_exit(led_exit);
