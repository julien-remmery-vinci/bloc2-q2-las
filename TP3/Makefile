# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

# Linker
npi : npi.o utils_v1.o pile.o
	cc $(CFLAGS) -o npi npi.o utils_v1.o pile.o

# Compilation
npi.o : npi.c
	cc $(CFLAGS) -c npi.c

utils_v1.o : utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

pile.o : pile.c
	cc $(CFLAGS) -c pile.c

clean :
	rm *.o npi 
