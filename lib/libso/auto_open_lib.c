#include<stdio.h>
#include"demo.h"

int main(){
	
	printf("data address:%p\n", &data);
	data.prnmsg("I am Horn, and you?");
	printf("data.value:%d\n", data.value);
	return 0;

}
