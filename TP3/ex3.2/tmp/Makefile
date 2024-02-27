# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

# Linker
testplaylist : testplaylist.o playlist.o
	cc $(CFLAGS) -o testplaylist testplaylist.o playlist.o

# Compilation
testplaylist.o : testplaylist.c
	cc $(CFLAGS) -c testplaylist.c

playlist.o : playlist.c
	cc $(CFLAGS) -c playlist.c

clean :
	rm *.o testplaylist 
