#include<stdio.h>
#include"head.h"

void init_data(struct data *datap){
	datap->x = 100;
	snprintf(datap->str, STRMAX, "test :%d", datap->x);
	printf("RESULT: %s\n", datap->str);
}

static void print(){
	printf("hhahha\n");
}
