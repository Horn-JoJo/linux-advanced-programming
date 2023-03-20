#include<stdio.h>
#include<unistd.h>
#include<string.h>

int caculate_num_of_value(char *path_value){
	int count = 0; 
	int len = strlen(path_value);
	int i;
	for(i = 0; i < len; i++){
		if(path_value[i] == ':')
			count++;	
	}
	return ++count;
}

char **split_env_value(char *path_value, int count){
	char **envp = (char **)malloc(sizeof(char *) * (count + 2));//2个空间一个存储新路径，一个作为结束符
	if(NULL == envp){
		perror("malloc");
		return NULL;
	}
	char *p = path_value;
	char *q = path_value;
	int i = 0;
	while(*q != '\0'){
		if(*q == ':' ){
			*q = '\0';
			int len = strlen(p);
			envp[i] = (char *)malloc(sizeof(char) * (len + 1));
			memset(envp[i], 0, sizeof(envp[i]));
			strcpy(envp[i], p);	
			p = q + 1;
			i++;
		}
		q++;
	}
	int len = strlen(p);
	envp[i] = (char *)malloc(sizeof(char) * (len + 1));
	memset(envp[i], 0, sizeof(envp[i]));
	strcpy(envp[i], p);	

	i++;
	static char *new_value = "/home/linux/2023/process/exec/";
	len = strlen(new_value);
	envp[i] = (char *)malloc(sizeof(char) * (len + 1));
	memset(envp[i], 0, sizeof(envp[i]));
	strcpy(envp[i], new_value);

	i++;
	envp[i] = NULL;

	return envp;
}

void print(char **envp, int count){
	int i;
	for(i = 0; i < count; i++){
		printf("envp[i] = %s\n", envp[i]);
	}
}

int main(){

	char *path_value = (char *)getenv("PATH");
	if(NULL == path_value){
		perror("getenv");
		return -1;
	}
	printf("path_value:%s\n", path_value);	
	
	//计算值字符串的个数
	int count = caculate_num_of_value(path_value);
	//printf("caculate_num_of_value:%d 个值字符串\n", count);
	//分割存储并存储
	//动态分配一个count+2个字符串数组
	char **envp = split_env_value(path_value, count);
	if(NULL == envp){
		return -1;
	}else{
		print(envp, count + 2);
	}


	char *arg[] = {
		"app",
		"123",
		"456",
		"789",
		NULL,
	};
	
	/*char *envp[] = {
		"/home/linux/2023/process/exec/",
		NULL,
	};这样设置根本不管用！！！*/


	if(0 > execvpe("app", arg, envp)){
		perror("execvpe");
		return -1;
	}

	printf("You are a good man!\n");
	return 0;
}
