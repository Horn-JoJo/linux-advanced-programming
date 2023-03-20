#include<stdio.h>
#include<string.h>

int main(){
	test_reopen();
	return 0;
}

#define MAX 1024
void test_read(){
	printf("------strat------\n");
	char buf[MAX];
	fgets(buf, MAX, stdin);

	int len = strlen(buf);
	printf("len = %d\n", len);
}

void test_write(){
	char msg[] = "hello world";
	//puts(msg);
	
	fputs(msg, stdout);
	fputs("\n", stdout);
	fputs(msg, stdout);
	fputs("\n", stdout);
}

void test_reopen(){
	printf("hello world!");
	puts("hhhhha");
	fputs("You are beautiful!", stdout);

	FILE *fp = freopen("2.txt", "a", stdout);
	if(NULL == fp){
		perror("freopen");
		return;
	}
	printf("sbbbb honghong!\n");
	puts("hhhhha");
	fputs("You are beautiful!\n", stdout);
	fclose(fp);

}
