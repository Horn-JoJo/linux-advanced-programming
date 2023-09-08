#include<stdio.h>

void test(){
	return;
}

int main(){
		
	printf("main addr:%p;test addr:%p\n", main, test);
	return 0;	
}
