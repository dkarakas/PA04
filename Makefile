TARGET = pa04
GCC = gcc
DEFINES = -DTEST_DIVIDE -DTEST_INTERLEAVE -DTEST_SHUFFLE
CFLAGS = -g -Wall -Wshadow -Werror $(DEFINES)
CC = $(GCC) $(CFLAGS) $(DEFINES)
SRCS = pa04.c answer04.c 
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test:
	$(VALGRIND)=./logfile ./pa04 lorum lorum.huffman lorum.char lorum.bit

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)
