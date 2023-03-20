#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	
	for(int i = 0; i < argc; i++){
		printf("input %d str:%s\n", i, argv[i]);
	}
	sleep(3);
	return 0;
}
