#include <stdarg.h>
extern const int inf;
int sub(int a, int b, ...)
{
	int res = a - b;

	va_list var_ptr;
	va_start(var_ptr, b);

	b = va_arg(var_ptr, int);

	while (b != inf)
	{
		res -= b;
		b = va_arg(var_ptr, int);
	}
	return res;
}

