TARGET = pe10
GCC = gcc
CFLAGS = -g -Wall -Wshadow -Werror
CC = $(GCC) $(CFLAGS)
SRCS = pe10.c answer10.c
OBJS = $(SRCS:%.c=%.c)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test:
	$(VALGRIND)=./logfile ./pe10 

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)
