#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef void * fun_t;


typedef struct  _sym_tab{
	char name[64];
	fun_t fun_addr;
}sym_tab_t;


static void fun_a(){
	printf("%s at line:%d\n", __func__, __LINE__);
}

static int fun_b(int a, int b){
	int res = a + b;
	printf("%s at line:%d, result:%d\n", __func__, __LINE__, res);
	return res;
}

static char* fun_c(char *a, char *b){
	int len_a = strlen(a);
	int len_b = strlen(b);
	char *c = (char *)malloc(sizeof(char) * (len_a + len_b + 1));
	strncpy(c, a, len_a);
	char *d = c + len_a;
	strncpy(d, b, len_b);
	c[len_a + len_b] = 0;
	printf("%s at line:%d ", __func__, __LINE__);
	return c;
}

sym_tab_t symbol_table[] = {
	{"fun_a", fun_a},
	{"fun_b", fun_b},
	{"fun_c", fun_c},
};


void *findsym(char *s){
	for (int i = 0; i < sizeof(symbol_table) / sizeof(symbol_table[0]); i++){
		if (!strcmp(s, symbol_table[i].name))
			return symbol_table[i].fun_addr;
	}
	return NULL;
}

int main(){
	char *(*str_cat)(char *, char *) = findsym("fun_c");
	if(str_cat){
		puts(str_cat("hello", "world"));
	}

	void (*pfuna)() = findsym("fun_a");
	if(pfuna){
		pfuna();
	}

	int (*pfunb)(int, int) = findsym("fun_b");
	if(pfunb){
		pfunb(260, 260);
	}
	
	return 0;
}
