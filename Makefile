CC = gcc
CFLAGS = -g -Wall -Werror

default: huff unhuff

huff: huff.o hftree.o minheap.o
	$(CC) $(CFLAGS) -o huff huff.o hftree.o

unhuff: unhuff.o hftree.o minheap.o
	$(CC) $(CFLAGS) -o unhuff unhuff.o hftree.o

test: # TODO

huff.o: huff.cc
	$(CC) $(CLFAGS) -c huff.cc

unhuff.o: unhuff.cc
	$(CC) $(CLFAGS) -c unhuff.cc

hftree.o: hftree.cc hftree.h
	$(CC) $(CLFAGS) -c hftree.cc

minheap.o: minheap.h

clean:
	rm -f huff
	rm -f unhuff
	rm -f *.o
	rm -f *.d

