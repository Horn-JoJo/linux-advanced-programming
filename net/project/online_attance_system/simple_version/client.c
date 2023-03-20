#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>



#define err_log(log)\
	do{\
		perror(log);\
		exit(1);\
	}while(0)

typedef struct sockaddr SA;

int main(int argc, const char *argv[])
{
	if (3 > argc) 
	{
		fprintf(stderr, "USER:%s IP PORT.\n", argv[0]);
		return -1;
	}

	int confd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > confd) err_log("socket");
	
	struct sockaddr_in seraddr = {
		.sin_family = AF_INET,
		.sin_port = htons(atoi(argv[2])),
		.sin_addr.s_addr = inet_addr(argv[1])
	};
	
	if (0 > connect(confd, (SA *)&seraddr, sizeof(seraddr))) err_log("connect");

	//从终端输入字符串到buf中
	printf("Please input something:\n");
	
	char buf[1024];
	bzero(buf, 1024);
	
	fgets(buf, 1024, stdin);

	int len = strlen(buf);
	buf[len - 1] = 0;
	
	//发送
	if (0 > send(confd, buf, sizeof(buf), 0)) err_log("send");
	close(confd);

	return 0;
}
