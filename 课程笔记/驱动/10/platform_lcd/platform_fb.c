#include<linux/module.h>
#include<linux/init.h>
#include<linux/platform_device.h>
#include<linux/fb.h>
#include<linux/dma-mapping.h>
#include<asm/io.h>

#define GPF0CON 0x0180
#define GPF1CON 0x01a0
#define GPF2CON 0x01c0
#define GPF3CON 0x01e0
#define GPD0CON 0xa0
#define GPD0DAT 0xa4
#define VIDCON0 0x00
#define VIDCON1 0x04
#define VIDCON2 0x08
#define VIDTCON0 0x10
#define VIDTCON1 0x14
#define VIDTCON2 0x18
#define WINCON0 0x20
#define SHADOWCON 0x34
#define VIDOSD0A 0x40
#define VIDOSD0B 0x44
#define VIDOSD0C 0x48
#define VIDW00ADD0B0 0xa0
#define VIDW00ADD1B0 0xd0
#define VIDW00ADD2 0x100

struct fb_info *fb;
dma_addr_t dma_map;
unsigned long pseudo_palette[16];

void __iomem *gpio_base;
struct resource *gpio_res;

void __iomem *lcd_src_lcd0;
struct resource *lcd_src_lcd0_res;

void __iomem *lcd_div_lcd;
struct resource *lcd_div_lcd_res;

void __iomem *lcdblk_cfg;
void __iomem *lcdblk_cfg2;
struct resource *lcdblk_cfg_res;

void __iomem *lcdcon_base;
struct resource *lcdcon_base_res;

static inline unsigned int fs_chan_to_field(unsigned int chan,
					 struct fb_bitfield *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	return chan << bf->offset;
}

static int fs_lcdfb_setcolreg(unsigned int regno, unsigned int red,
			     unsigned int green, unsigned int blue,
			     unsigned int transp, struct fb_info *info)
{
	unsigned int val = 0;
	if (regno < 16) {
		unsigned int *pal = info->pseudo_palette;
		val = fs_chan_to_field(red, &info->var.red);
		val |= fs_chan_to_field(green, &info->var.green);
		val |= fs_chan_to_field(blue, &info->var.blue);
		pal[regno] = val;
	}else{
		printk("fs_lcdfb_setcolreg rangno so big !\n");	
	}
	return 0;
}

struct fb_ops fs4412_fbops = {
	.owner = THIS_MODULE,
	.fb_setcolreg = fs_lcdfb_setcolreg,
	.fb_fillrect = cfb_fillrect,
	.fb_copyarea = cfb_copyarea,
	.fb_imageblit = cfb_imageblit,
};

int fs4412_lcd_probe(struct platform_device *pdev)
{
	int ret;
	printk("match ok\n");

	fb = framebuffer_alloc(0,NULL);
	strcpy(fb->fix.id,"fslcd");    //对lcd固定参数结构体填充
	fb->fix.smem_len = 1024 * 600 * 2;
	fb->fix.type = FB_TYPE_PACKED_PIXELS;
	fb->fix.visual = FB_VISUAL_TRUECOLOR;
	fb->fix.line_length = 1024 * 2;

	fb->var.xres = 1024;      //lcd可变参数结构体填充
	fb->var.yres = 600;
	fb->var.xres_virtual = 1024;
	fb->var.yres_virtual = 600;
	fb->var.xoffset = 0;
	fb->var.yoffset = 0;

	fb->var.bits_per_pixel = 16;
	fb->var.red.offset = 11;
	fb->var.red.length = 5;
	fb->var.green.offset = 5;
	fb->var.green.length = 6;
	fb->var.blue.offset = 0;
	fb->var.blue.length = 5;
	fb->var.activate = FB_ACTIVATE_NOW;

	fb->fbops = &fs4412_fbops;

	fb->screen_size = 1024 * 600 * 2;
	fb->screen_base = dma_alloc_writecombine(NULL,fb->screen_size,&dma_map,GFP_KERNEL);
	fb->fix.smem_start = dma_map;
	fb->pseudo_palette = pseudo_palette;

	gpio_res = platform_get_resource(pdev,IORESOURCE_MEM,0);	
	gpio_base = ioremap(gpio_res->start,4);

	writel(0x22222222,gpio_base + GPF0CON);			
	writel(0x22222222,gpio_base + GPF1CON);			
	writel(0x22222222,gpio_base + GPF2CON);			
	writel(0x222222,gpio_base + GPF3CON);			
	writel(1 << 4,gpio_base + GPD0CON);

	lcd_src_lcd0_res = platform_get_resource(pdev,IORESOURCE_MEM,1);
	lcd_src_lcd0 = ioremap(lcd_src_lcd0_res->start,4);

	lcd_div_lcd_res = platform_get_resource(pdev,IORESOURCE_MEM,2);
	lcd_div_lcd = ioremap(lcd_div_lcd_res->start,4);

	writel((readl(lcd_src_lcd0) & ~0xf) | 6,lcd_src_lcd0);
	writel((readl(lcd_div_lcd) & ~0xf),lcd_div_lcd);

	lcdblk_cfg_res = platform_get_resource(pdev,IORESOURCE_MEM,3);
	lcdblk_cfg = ioremap(lcdblk_cfg_res->start,4);
	lcdblk_cfg2 = lcdblk_cfg + 4;

	writel(1 << 1,lcdblk_cfg);
	writel(readl(lcdblk_cfg2) | 1,lcdblk_cfg2);

	lcdcon_base_res = platform_get_resource(pdev,IORESOURCE_MEM,4);
	lcdcon_base = ioremap(lcdcon_base_res->start,4);

	writel((readl(lcdcon_base + VIDCON0) & ~(0xf << 6)) | (14 << 6),lcdcon_base + VIDCON0);
	writel((readl(lcdcon_base + VIDCON1) & ~(1 << 7)) | (1 << 5) | (1 << 6) | 1 << 9,lcdcon_base + VIDCON1);
	writel((readl(lcdcon_base + VIDCON2) | (1 << 14)),lcdcon_base + VIDCON2);
	
	writel(readl(lcdcon_base + VIDTCON0) | (10 << 0) | (12 << 8) | (14 << 16),lcdcon_base + VIDTCON0);
	writel(readl(lcdcon_base + VIDTCON1) | (40 << 0) | (160 << 8) | (120 << 16),lcdcon_base + VIDTCON1);
	writel(readl(lcdcon_base + VIDTCON2) | (1023 << 0) | (599 << 11),lcdcon_base + VIDTCON2);

	writel((readl(lcdcon_base + WINCON0) & ~(0xf << 2)) | (5 << 2) | (0 << 9) | (1 << 16),lcdcon_base + WINCON0);
	writel(readl(lcdcon_base + SHADOWCON) | 1,lcdcon_base + SHADOWCON);

	writel(readl(lcdcon_base + VIDOSD0A) | (0 << 0) | (0 << 11),lcdcon_base + VIDOSD0A);
	writel(readl(lcdcon_base + VIDOSD0B) | (599 << 0) | (1023 << 11),lcdcon_base + VIDOSD0B);
	writel(readl(lcdcon_base + VIDOSD0C) | (1024 * 600),lcdcon_base + VIDOSD0C);
	writel(readl(lcdcon_base + VIDW00ADD0B0) | fb->fix.smem_start,lcdcon_base + VIDW00ADD0B0);
	writel(readl(lcdcon_base + VIDW00ADD1B0) | (fb->fix.smem_start + fb->fix.smem_len),lcdcon_base + VIDW00ADD1B0);
	writel(readl(lcdcon_base + VIDW00ADD2) | (0 << 13) | (1024 * 2),lcdcon_base + VIDW00ADD2);

	writel(readl(lcdcon_base + VIDCON0) | 3,lcdcon_base + VIDCON0);
	writel(readl(lcdcon_base + WINCON0) | 1,lcdcon_base + WINCON0);
	writel(1 << 1,gpio_base + GPD0DAT);
	ret = register_framebuffer(fb);

	printk("init success\n");
	return 0;
}

int fs4412_lcd_remove(struct platform_device *pdev)
{
	return 0;
}

struct of_device_id fs4412_lcd_match_table[] = {
	{
		.compatible = "fs4412,lcd",
	},
	{},
};

struct platform_driver fb_drv = {
	.driver = {
		.name = "fs4412-lcd",
		.of_match_table = fs4412_lcd_match_table,
	},
	.probe = fs4412_lcd_probe,
	.remove = fs4412_lcd_remove,
};
module_platform_driver(fb_drv);
MODULE_LICENSE("GPL");
