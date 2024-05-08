CC=gcc
CCOPTS=-Wall -Wextra -Werror -DCTEST_ENABLE
LIBS=libvvsfs.a

SRCS=$(wildcard *.o)
TARGETS=$(SRCS:.c=)

.PHONY: clean pristine test

test: testfs
	./testfs

testfs: libvvsfs.a
	$(CC) $(CCOPTS) -o $@ $(LIBS)

libvvsfs.a: block.o image.o free.o testfs.o
	ar rcs $@ $^

block.o: block.c
	$(CC) $(CCOPTS) -c $^

image.o: image.c
	$(CC) $(CCOPTS) -c $^

free.o: free.c
	$(CC) $(CCOPTS) -c $^

testfs.o: testfs.c
	$(CC) $(CCOPTS) -c $^

clean:
	rm -f $(TARGETS)
pristine: clean
	rm -f libvvsfs.a testfs image.txt