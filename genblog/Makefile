CC=clang
LIBS=-lcurl
CFLAGS=-c -Wall
EXTS=zstr/*.c

EXECNAME=genblog

all: genblog 

test: clean all run

genblog: cfiles 
	$(CC) $(LIBS) *.o -o $(EXECNAME)

cfiles:
	$(CC) $(CFLAGS) $(EXTS) *.c

clean:
	rm -rf *.o $(EXECNAME)

run:
	cd .. && ./genblog/genblog 
