struct dev 
{
	char name[15];
	int a;
	int b;
};

struct drv 
{
	char name[15];
	int (*p)(struct dev *);
};
