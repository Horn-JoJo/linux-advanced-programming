#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define MAX 1024
int main(){
	int fd[2];
	
	if(0 > pipe(fd)){
		perror("pipe");
		return -1;
	}
	
	pid_t pid;
	pid = fork();
	if(0 > pid){
		perror("fork");
		return -1;
	}else if(0 == pid){
		//receive
		printf("son is running.\n");
		close(fd[0]);
		int i = 0;
		while(1){
			char buf[] = "hello world";
			int len = strlen(buf);
			
			if(4 != write(fd[1], &len, 4)){
				printf("send protocal head fail.\n");
				break;
			}
			if(len != write(fd[1], buf, len)){
				printf("write fail.\n");
				break;
			}else{
				printf("NO:%d write %s : %d bytes success.\n", i++, buf, len);
			}
		}
		close(fd[1]);
		printf("son is over.\n");
	}else{
		//send
		printf("father is running.\n");
		close(fd[1]);
		while(1){
			char buf[MAX];
			int len, size;
			char *p = &len;
			int num = 4;
			while(num){
				size = read(fd[0], p, num);
				if(0 > size){
					perror("read.\n");
					return -1;
				}
				num -= size;
				p += size;
			}


			if(len >= MAX){
				printf("No more space\n");
				return -1;
			}
			p = buf;
			size = len;
			while(len){
				num = read(fd[0], p, len);
				if(0 > num){
					perror("read.\n");
					return -1;
				}
				len -= num;
				p += num;
			}
			buf[size] = 0;
			printf("receive buf:%s ->%d bytes\n", buf, size);
		}
		close(fd[0]);
		printf("father is over.\n");
	}
	return 0;

}
