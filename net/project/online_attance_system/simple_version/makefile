CC = gcc
CFLAG = -Wall -O2 -g
OBJS = $(patsubst %.c, %.o, $(wildcard %.c))
server : server.o
	$(CC) $(CFLAG) $< -o $@
client : client.o
	$(CC) $(CFLAG) $< -o $@
.PHONY : clean
clean:
	rm -rf server client  *.o

