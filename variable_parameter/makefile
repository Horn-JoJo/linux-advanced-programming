#定义CC变量表示gcc编译器
CC = gcc 

#定义最终生成可执行程序名为APP
APP = main 

#内键函数！！！
#patsubst 把所指定的.c文件自动生成对应的.o文件 
#wildcard 把当前所有的.c文件找到
OBJS = $(patsubst %.c, %.o, $(wildcard *.c)) 

#makefile 已经存在的编译参数变量CFLAGS 不需要显示加CFLAGS 编译时会自动加上！！！
CFLAGS += -Wall -O2 -g -fPIC -std=gnu99

$(APP) : $(OBJS) #当目标不存在或者依赖体更新时，下面的命令会走一遍
	$(CC) -o $@ $^
	./main
clean:
	rm $(OBJS) $(APP)

break:
	sl
