#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getMemory(char **q)
{
	*q = (char *)malloc(100 * sizeof(char));
}

int main()
{
	char *p = NULL;

	getMemory(&p);
	strcpy(p, "hello world!");
	puts(p);
	free(p);

	return 0;
}
