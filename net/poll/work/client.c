#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

typedef struct sockaddr SA;
typedef struct sockaddr_in SAI;
int confd;

void handler(int sig)
{
	close(confd);
	exit(0);
}

int main()
{
	signal(SIGINT, handler);
	confd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > confd)
	{
		perror("socket");
		return -1;
	}

	SAI seraddr = 
	{
		.sin_family = AF_INET,
		.sin_port = htons(9999),
		.sin_addr.s_addr = inet_addr("192.168.181.128")
	};

	if (0 > connect(confd, (SA *)&seraddr, sizeof(seraddr)))
	{
		perror("connect");
		return -1;
	}

	char buf[1024] = {0};

	while (1)
	{
		printf("Please input:");
		fgets(buf, 1024, stdin);

		buf[strlen(buf) - 1] = 0;

		send(confd, buf, strlen(buf), 0);
		printf("send:%s\n", buf);
	}
	return 0;
}
