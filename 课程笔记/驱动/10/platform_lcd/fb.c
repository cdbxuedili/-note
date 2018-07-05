#include<linux/init.h>
#include<linux/module.h>
#include<linux/fb.h>
#include<linux/dma-mapping.h>

#define GPF0CON 0x11400180
#define GPF1CON 0x114001A0
#define GPF2CON 0x114001C0
#define GPF3CON 0x114001E0
#define GPD0CON 0x114000a0
#define LCDBLK_CFG 0x10010210
#define LCDBLK_CFG2 0x10010214
#define CLK_SRC_LCD0 0x1003c234
#define CLK_DIV_LCD 0x1003c534
#define VIDCON0 0x11c00000
#define VIDCON1 0x11c00004
#define VIDCON2 0x11c00008
#define VIDTCON0 0x11c00010
#define VIDTCON1 0x11c00014
#define VIDTCON2 0x11c00018
#define WINCON0 0x11c00020
#define SHADOWCON 0x11c00034
#define WINCHMAP2 0x11c0003c
#define VIDOSD0A 0x11c00040
#define VIDOSD0B 0x11c00044 
#define VIDOSD0C 0x11c00048
#define VIDW00ADD0B0 0x11c000a0
#define VIDW00ADD1B0 0x11c000d0
#define VIDW00ADD2 0x11c00100
#define WIN0MAP 0x11c00180

unsigned int *gpf0con;
unsigned int *gpf1con;
unsigned int *gpf2con;
unsigned int *gpf3con;
unsigned int *lcdblk_cfg;
unsigned int *lcdblk_cfg2;
unsigned int *gpd0con;
unsigned int *gpd0dat;
unsigned int *clk_src_lcd0;
unsigned int *vidcon0;
unsigned int *vidcon1;
unsigned int *vidcon2;
unsigned int *vidtcon0;
unsigned int *vidtcon1;
unsigned int *vidtcon2;
unsigned int *wincon0;
unsigned int *shadowcon;
unsigned int *winchmap2;
unsigned int *vidosd0a;
unsigned int *vidosd0b;
unsigned int *vidosd0c;
unsigned int *vidw00add0b0;
unsigned int *vidw00add1b0;
unsigned int *vidw00add2;
unsigned int *win0map;
unsigned int *clk_div_lcd;

struct fb_info *fb;
dma_addr_t dma_map;

unsigned long pseudo_palette[16];
#if 1
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
#endif
struct fb_ops fs4412_fbops = {
	.owner = THIS_MODULE,
	.fb_setcolreg = fs_lcdfb_setcolreg,
	.fb_fillrect = cfb_fillrect,
	.fb_copyarea = cfb_copyarea,
	.fb_imageblit = cfb_imageblit,
};

int fs4412_fb_init(void)
{
	int ret;
	fb = framebuffer_alloc(0,NULL);

	strcpy(fb->fix.id,"fslcd");
	fb->fix.smem_len = 1024 * 600 * 2;
	fb->fix.type = FB_TYPE_PACKED_PIXELS;
	fb->fix.visual = FB_VISUAL_TRUECOLOR;
	fb->fix.line_length = 1024 * 2;

	fb->var.xres = 1024;
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

// 	寄存器配置
	gpf0con = ioremap(GPF0CON,4);
	gpf1con = ioremap(GPF1CON,4);
	gpf2con = ioremap(GPF2CON,4);
	gpf3con = ioremap(GPF3CON,4);
	gpd0con = ioremap(GPD0CON,4);
	gpd0dat = gpd0con + 1;

	writel(0x22222222,gpf0con);
	writel(0x22222222,gpf1con);
	writel(0x22222222,gpf2con);
	writel(0x222222,gpf3con);
	writel(1 << 4,gpd0con);

	clk_div_lcd = ioremap(CLK_DIV_LCD,4);
	clk_src_lcd0 = ioremap(CLK_SRC_LCD0,4);//选择时钟源
	lcdblk_cfg = ioremap(LCDBLK_CFG,4);
	lcdblk_cfg2 = ioremap(LCDBLK_CFG2,4);
	vidcon0 = ioremap(VIDCON0,4);
	vidcon1 = ioremap(VIDCON1,4);
	vidcon2 = ioremap(VIDCON2,4);
	vidtcon0 = ioremap(VIDTCON0,4);
	vidtcon1 = ioremap(VIDTCON1,4);
	vidtcon2 = ioremap(VIDTCON2,4);
	wincon0 = ioremap(WINCON0,4);
	shadowcon = ioremap(SHADOWCON,4);
	vidosd0a = ioremap(VIDOSD0A,4);
	vidosd0b = ioremap(VIDOSD0B,4);
	vidosd0c = ioremap(VIDOSD0C,4);
	vidw00add0b0 = ioremap(VIDW00ADD0B0,4);
	vidw00add1b0 = ioremap(VIDW00ADD1B0,4);
	vidw00add2 = ioremap(VIDW00ADD2,4);

	writel((readl(clk_div_lcd) & (~0xf)),clk_div_lcd);//这句话不加会刷屏
	writel((readl(clk_src_lcd0) & ~0xf) | 6,clk_src_lcd0);
	//如果需要分频则设置CLK_DIV_LCD,这里我们不分频

	writel(1 << 1,lcdblk_cfg);
	writel((readl(lcdblk_cfg2)|(1)),lcdblk_cfg2);

	writel((readl(vidcon0) & ~(0xf << 6)) | (14 << 6),vidcon0);
	writel((readl(vidcon1) & ~(1 << 7)) | (1 << 5) | (1 << 6) | (1 << 9),vidcon1);
	writel(readl(vidcon2) | (1 << 14),vidcon2);
	writel(readl(vidtcon0) | (10 << 0) | (12 << 8) | (14 << 16),vidtcon0);
	writel(readl(vidtcon1) | (40 << 0) | (160 << 8) | (120 << 16),vidtcon1);
	writel(readl(vidtcon2) | (1023 << 0) | (599 << 11),vidtcon2);
	writel((readl(wincon0) & ~(0xf << 2)) | (5 << 2) | (0 << 9) | (1 << 16),wincon0);
	writel(readl(shadowcon) | 1,shadowcon);
//	winchmap2 = ioremap(WINCHMAP2,4);
	writel(readl(vidosd0a) | (0 << 0) | (0 << 11),vidosd0a);
	writel(readl(vidosd0b) | (599 << 0) | (1023 << 11),vidosd0b);
	writel(readl(vidosd0c) | (1024 * 600),vidosd0c);
	writel(readl(vidw00add0b0) | fb->fix.smem_start,vidw00add0b0);
	writel(readl(vidw00add1b0) | (fb->fix.smem_start + fb->fix.smem_len),vidw00add1b0);
	writel(readl(vidw00add2) | (0 << 13) | (1024 * 2),vidw00add2);

//	win0map = ioremap(WIN0MAP,4);
//	writel(readl(win0map) & 0,win0map);

	writel(readl(vidcon0) | 3,vidcon0);
	writel(readl(wincon0) | 1,wincon0);
	writel(1 << 1,gpd0dat);

	ret = register_framebuffer(fb);
	printk("init success\n");
	return 0;
}
module_init(fs4412_fb_init);

void fs4412_fb_exit(void)
{
	return ;
}
module_exit(fs4412_fb_exit);
MODULE_LICENSE("GPL");
