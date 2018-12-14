CC = g++
CFLAGS = -g -Wall -Werror

default: huff unhuff

huff: huff.o hftree.o minheap.o charcounter.o
	$(CC) $(CFLAGS) -o huff huff.o hftree.o

unhuff: unhuff.o hftree.o minheap.o charcounter.o
	$(CC) $(CFLAGS) -o unhuff unhuff.o hftree.o

test: test.o hftree.o minheap.o charcounter.o
	$(CC) $(CFLAGS) -o test test.o hftree.o

huff.o: huff.cc
	$(CC) $(CFLAGS) -c huff.cc

unhuff.o: unhuff.cc
	$(CC) $(CFLAGS) -c unhuff.cc

hftree.o: hftree.cc hftree.h
	$(CC) $(CFLAGS) -c hftree.cc

charcounter.o: charcounter.h

minheap.o: minheap.h

test.o: test.cc
	$(CC) $(CFLAGS) -c test.cc

clean:
	rm -f huff
	rm -f unhuff
	rm -f test
	rm -f *.o
	rm -f *.d

