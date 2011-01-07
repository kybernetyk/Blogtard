CC=clang
LIBS=-lcurl
CFLAGS=-c -Wall

EXECNAME=genblog

all: genblog 

test: clean all run

genblog: cfiles 
	$(CC) $(LIBS) *.o -o $(EXECNAME)

cfiles:
	$(CC) $(CFLAGS) *.c

clean:
	rm -rf *.o $(EXECNAME)

run:
	cd .. && ./genblog/genblog 
