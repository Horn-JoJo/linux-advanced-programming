#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>


void setnoblock(int fd) {
	int flags = fcntl(fd, F_GETFL);
	
	flags |= O_NONBLOCK;
	if (0 > fcntl(fd, F_SETFL, flags)) {
		perror("fcntl");
		exit(0);
	}

}


int main(){
	//setnoblock(0);

#if 0
	char ch[1];
	read(0, ch, 1);
#else
	char ch;
	if (0 > read(0, &ch, 1)) {
		perror("read");
	}else {
		printf("ch = %c\n", ch);
	}
#endif

	return 0;
}
