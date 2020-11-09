TARGET = pe08
GCC = gcc
CFLAGS = -g -Wall -Wshadow -Werror
CC = $(GCC) $(CFLAGS)
SRCS = pe08.c answer08.c
OBJS = $(SRCS:%.c=%.c)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test:
	$(VALGRIND)=./logfile ./pe08 

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)
