#include<stdio.h>


typedef void * T;


void myopen(){
	printf("%s:%d\n", __func__, __LINE__);
}

void myread(){
	printf("%s:%d\n", __func__, __LINE__);
}

void mywrite(){
	printf("%s:%d\n", __func__, __LINE__);
}

void myclose(){
	printf("%s:%d\n", __func__, __LINE__);
}

T fun_list[] = {
	myopen,
	myread,
	mywrite,
	myclose,
};

#define ARRAY(a) (sizeof(a) / sizeof(a[0]))


void syscall(int fun_num){
	if(0 <= fun_num && fun_num < ARRAY(fun_list)){
		void (*pfun) () = fun_list[fun_num];
		pfun();
	}
}

#define SYS_open 0
#define SYS_read 1
#define SYS_write 2
#define SYS_close 3



int main(){

	syscall(SYS_open);
	syscall(SYS_read);
	syscall(SYS_write);
	syscall(SYS_close);
	
	return 0;
}
