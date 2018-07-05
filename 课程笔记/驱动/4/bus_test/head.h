
struct dev
{
	int a;
	int b;
};

struct drv
{
	int (*p)(struct dev *);
};
