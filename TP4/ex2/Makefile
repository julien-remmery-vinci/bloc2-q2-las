# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all : biblioMaj 

# Linker
biblioMaj: biblioMaj.o biblio.o utils_v1.o
	cc $(CFLAGS) -o biblioMaj biblioMaj.o biblio.o utils_v1.o

# Compilation
biblio.o : biblio.c 
	cc $(CFLAGS) -c biblio.c 

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

clean :
	rm *.o biblioMaj 
