#include "head.h"



int main()
{
	LINKLIST *L;
	int i;

	L = create_empty_linklist();

	for(i = 0; i < 10;i ++)
		insert_head_linklist(L,i);

	print_linklist(L);

	delete_assign_linklist(L,2);
	print_linklist(L);

	delete_assign_linklist(L,9);
	print_linklist(L);

	return 0;
}
