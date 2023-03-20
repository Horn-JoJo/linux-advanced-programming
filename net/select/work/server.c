#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>


typedef struct sockaddr SA;
typedef struct sockaddr_in SAI;

char buf[1024];
fd_set fds, rfd;
int maxfd;

int main()
{

	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > listenfd)
	{
		perror("socket");
		return -1;
	}

	SAI srvaddr = 
	{
		.sin_family = AF_INET,
		.sin_port = htons(9999),
		.sin_addr.s_addr = inet_addr("192.168.0.106")
	};	

	SAI cliaddr;
	socklen_t addrlen = sizeof(cliaddr);

	if (0 > bind(listenfd, (SA *)&srvaddr, sizeof(srvaddr)))
	{
		perror("bind");
		return -1;
	}

	if (0 > listen(listenfd, 15))
	{
		perror("listen");
		return -1;
	}
	
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	FD_SET(listenfd, &fds);
	maxfd = listenfd;
	int i;	

	while (1)
	{
		rfd = fds;
		struct timeval tv = {1};
		int ret = select(maxfd + 1, &rfd, NULL, NULL, /*NULL*/&tv);
		if (0 > ret)
		{
			perror("select");
			break;
		}
		else if (0 == ret)
		{
			printf("timeout......\n");
			continue;
		}
		else
		{
			for (i = 0; i < maxfd + 1; i++)
			{
				if (FD_ISSET(i, &rfd))
				{
					if (0 == i)
					{
						fgets(buf, 1024, stdin);
						fputs(buf, stdout);
						memset(buf, 0, sizeof(buf));
					}
					else if (listenfd == i)
					{
						int confd = accept(listenfd, (SA *)&cliaddr, &addrlen);
						if (0 > confd) 
						{
							perror("accept");
							continue;
						}
						printf("client[%s] connect successfully\n", inet_ntoa(cliaddr.sin_addr));
						FD_SET(confd, &fds);
						maxfd = (maxfd > confd) ? maxfd : confd;
					}
					else
					{
						int size = recv(i, buf, sizeof(buf), 0);
						if (0 > size)
						{
							perror("recv");
							continue;
						}
						else if (0 == size)
						{
							printf("client exit.\n");
							FD_CLR(i, &fds);
							close(i);
							continue;
						}
						printf("recv:%s\n", buf);
						memset(buf, 0, sizeof(buf));
					}
				}
			}
		}
	}

	close(listenfd);
	return 0;
}
