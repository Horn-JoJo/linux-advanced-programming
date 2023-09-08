#ifndef HEAD_H
#define HEAD_H

#define STRMAX 36
typedef struct data{
	int x;
	char str[STRMAX];
}data_t;

void init_data(data_t *datap);
static void print();
#endif
