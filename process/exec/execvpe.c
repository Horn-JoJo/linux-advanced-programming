#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){

	char *path_value = (char *)getenv("PATH");
	if(NULL == path_value){
		perror("getenv");
		return -1;
	}
	//printf("path_value:%s\n", path_value);	
	char new_env[1024];
	snprintf(new_env, 1024, "%s:/home/linux/2023/process/exec/", path_value);

	if(setenv("PATH", new_env, 1)){
	  perror("setenv");
	  return -1;
	}

	char *arg[] = {
		"newname",
		"-la",
		NULL,
	};

	if(0 > execvpe("/bin/ls", arg, (char **)NULL)){
		perror("execvpe");
		return -1;
	}

	printf("You are a good man!\n");
	return 0;
}
