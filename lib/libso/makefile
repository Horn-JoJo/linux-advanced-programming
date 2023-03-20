CC = gcc
LIBS = libdemo.so
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
CFLAGS += -Wall -O2 -g -fPIC -std=gnu99 -DMYDBG -I .
LDFLAGS += -shared

$(LIBS) : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(LIBS)

