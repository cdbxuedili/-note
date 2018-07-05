struct test 
{
	int a;
	char b;
};


#define TEST_CMD1 	_IO('x',0)
#define TEST_CMD2   _IO('x',1)
#define TEST_CMD3   _IOW('x',2,int)
#define TEST_CMD4   _IOW('x',3,int)
#define TEST_CMD5   _IOR('x',4,struct test)
