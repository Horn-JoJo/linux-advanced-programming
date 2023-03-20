#include<stdio.h>

typedef unsigned int bit_t;
typedef unsigned int uint32;


uint32 set_bits(bit_t bits, uint32 val){
	bit_t mask = 0x01;
	mask <<= bits;
	val |= mask;
	return val;
}

uint32 clear_bits(bit_t bits, uint32 val){
	bit_t mask = 0x01;
	mask <<= bits;
	val &= ~mask;
	return val;
}


int main(){
	int val = 10;
	printf("set_bits 第二位:%d\n", val = set_bits(2, val));//14
	printf("clear_bits 第三位:%d\n", val = clear_bits(3, val));//2
	return 0;
}
