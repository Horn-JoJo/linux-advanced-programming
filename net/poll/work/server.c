#include <stdio.h>
#include <poll.h>
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
		.sin_addr.s_addr = inet_addr("192.168.181.128")
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
	
	/*FD_ZERO(&fds);
	FD_SET(0, &fds);
	FD_SET(listenfd, &fds);
	maxfd = listenfd;*/
	//int i;	
	struct pollfd fds[1024];
	int num = 0;
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	num++;
	fds[1].fd = listenfd;
	fds[1].events = POLLIN;
	num++;

	while (1)
	{
		int ret = poll(fds, num, 1000);
		if (0 > ret)
		{
			perror("poll");
			break;
		}
		else if (0 == ret)
		{
			printf("timeout......\n");
			continue;
		}
		else
		{
			for (int i = 0; i < num; i++)
			{
				if (fds[i].revents & POLLIN)
				{
					if (0 == fds[i].fd)
					{
						fgets(buf, 1024, stdin);
						fputs(buf, stdout);
						memset(buf, 0, sizeof(buf));
					}
					else if (listenfd == fds[i].fd)
					{
						int confd = accept(listenfd, (SA *)&cliaddr, &addrlen);
						if (0 > confd) 
						{
							perror("accept");
							continue;
						}
						printf("client[%s] connect successfully\n", inet_ntoa(cliaddr.sin_addr));
						int j;
						for (j = 0; j < num; j++)
						{
							if (fds[j].fd == -1)
							{
								fds[j].fd = confd;
								fds[j].events = POLLIN;
								break;
							}
						}
						if (j == num)
						{
							fds[num].fd = confd;
							fds[num].events = POLLIN;
							num++;
							printf("num = %d \n", num);
						}
					}
					else if (fds[i].fd)//通信套接字
					{
						int size = recv(fds[i].fd, buf, sizeof(buf), 0);
						if (0 > size)
						{
							perror("recv");
							continue;
						}
						else if (0 == size)
						{
							printf("client exit.\n");
							close(fds[i].fd);
							fds[i].fd = -1;
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
