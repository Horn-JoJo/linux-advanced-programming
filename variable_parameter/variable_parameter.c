#include <stdio.h>
#include <stdarg.h>
int add(int a, ...)
{
	int sum = 0;
	//定义 参数指针
	va_list var_ptr;
	//var_ptr 指向第一个参数的地址
	va_start(var_ptr, a);
	//根据设计的参数类型 取下一个参数地址的值
	sum += a;
	a = va_arg(var_ptr, int);
	sum += a;
	while (a)
	{
		a = va_arg(var_ptr, int);
		printf("cur_arg_val = %d\n", a);
		sum += a;
	}
	return sum;
}
int main()
{
	int res = add(1, 2, 3, 4, 5, 6, 7, 8, 9, 0);
	printf("res = %d\n", res);
	return 0;
}
