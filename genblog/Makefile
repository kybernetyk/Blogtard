CC=clang
LIBS=-lcurl
CFLAGS=-c -Wall
ZSTR=zstr/

EXECNAME=genblog

all: genblog 

test: clean all run

genblog: cfiles 
	$(CC) $(LIBS) *.o -o $(EXECNAME)

cfiles:
	$(CC) $(CFLAGS) $(ZSTR)/*.c *.c

clean:
	rm -rf *.o $(EXECNAME)

run:
	cd .. && ./genblog/genblog 
