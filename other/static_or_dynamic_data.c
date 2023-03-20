#include<stdio.h>

int k = 0;

void test(){
	int i;
	printf("i = %p\n", &i);
	printf("k = %p\n", &k);
	puts("*****************");
	if(10 < k++){
		return;	
	}
	test();
}

int main(){
	test();
}
