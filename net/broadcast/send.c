#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX 1024
typedef struct sockaddr_in SAI;
typedef struct sockaddr SA;
char buf[MAX];

int main()
{
	int connfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (0 > connfd)
	{
		perror("socket");
		return -1;
	}

	int on = 1;
	if (0 > setsockopt(connfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)))
	{
		perror("setsockopt");
		close(connfd);
		return -1;
	}

	SAI rcvaddr = {
		.sin_family = AF_INET,
		.sin_port = htons(8888),
		.sin_addr.s_addr = inet_addr("192.168.181.255")
	};

	while (1)
	{
		memset(buf, 0, sizeof(buf));
		fgets(buf, MAX, stdin);

		if (strncmp(buf, "quit", 4) == 0) break;

		sendto(connfd, buf, strlen(buf), 0, (SA *)&rcvaddr, sizeof(rcvaddr));
	}

	close(connfd);
	return 0;
}
