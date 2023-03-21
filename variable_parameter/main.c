#include <stdio.h>
#include <stdarg.h>
#include "add.h"
#include "sub.h"


int main()
{
	printf("add = %d\n", add(1, 2, 3, 4, 5, 6, 7, 8, 9, 0));
	printf("sub = %d\n", sub(99, 88, 77, 55, 44, 33, 22, 11, inf));
	return 0;
}
