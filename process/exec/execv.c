#include<stdio.h>
#include<unistd.h>


int main(){
	int s = 3;
	while(s){
		printf("距离鸠占鹊巢还有：%d 秒\n", s--);
		sleep(1);
	}
	char *arg[] = {
		"world",
		"123",
		"456",
		"789",
		NULL
	};
	if(0 > execv("/APP/app", arg)){
		perror("execv");
		return -1;
	}

	printf("You are beautiful!\n");
	return 0;
}
