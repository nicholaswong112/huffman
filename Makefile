CC = g++
CFLAGS = -g -Wall -Werror

default: huff unhuff

huff: huff.o hftree.o minheap.o charcounter.o
	$(CC) $(CFLAGS) -o huff huff.o hftree.o charcounter.o

unhuff: unhuff.o hftree.o minheap.o charcounter.o
	$(CC) $(CFLAGS) -o unhuff unhuff.o hftree.o charcounter.o

test: test.o hftree.o minheap.o charcounter.o
	$(CC) $(CFLAGS) -o test test.o hftree.o charcounter.o

huff.o: huff.cc
	$(CC) $(CLFAGS) -c huff.cc

unhuff.o: unhuff.cc
	$(CC) $(CLFAGS) -c unhuff.cc

hftree.o: hftree.cc hftree.h
	$(CC) $(CLFAGS) -c hftree.cc

charcounter.o: charcounter.cc charcounter.h
	$(CC) $(CLFAGS) -c charcounter.cc

minheap.o: minheap.h

test.o: test.cc
	$(CC) $(CLFAGS) -c test.cc

clean:
	rm -f huff
	rm -f unhuff
	rm -f test
	rm -f *.o
	rm -f *.d

