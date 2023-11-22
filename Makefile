CC = gcc
CFLAGS = -Wall -g

all: myheaptest testheap testnocoalesce cardheap

heapmgr.o: heapmgr.c heapmgr.h
	$(CC) $(CFLAGS) -c heapmgr.c 

test_heap.o: test_heap.c heapmgr.h
	$(CC) $(CFLAGS) -c test_heap.c

.PHONY: clean
clean:
	@-rm -f *.o testheap testnocoalesce myheaptest cardheap

myheaptest: test_heap.o heapmgr.o
	$(CC) $(CFLAGS) -o myheaptest test_heap.o heapmgr.o

testheap: test_heap.o solution.o
	$(CC) $(CFLAGS) -o testheap test_heap.o solution.o

testnocoalesce: test_heap.o nocoalesce.o
	$(CC) $(CFLAGS) -o testnocoalesce test_heap.o nocoalesce.o 

cardheap: card.o cardmain.o cardlist.o heapmgr.o
	$(CC) $(CFLAGS) -o cardheap card.o cardmain.o cardlist.o heapmgr.o

card.o: card.c card.h
	$(CC) $(CFLAGS) -c card.c

cardmain.o: cardmain.c card.h cardlist.h
	$(CC) $(CFLAGS) -c cardmain.c

cardlist.o: cardlist.c card.h cardlist.h heapmgr.h
	$(CC) $(CFLAGS) -c cardlist.c

solution.o:
	ln -s /home/hdbui/shared/cs366/pa4/solution.o
nocoalesce.o:
	ln -s /home/hdbui/shared/cs366/pa4/nocoalesce.o
