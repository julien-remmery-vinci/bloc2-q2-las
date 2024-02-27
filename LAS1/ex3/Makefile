# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

lire: lire.o utils_v1.o
	cc $(CFLAGS) -o lire lire.o utils_v1.o

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

lire.o: lire.c
	cc $(CFLAGS) -c lire.c

clean:
	rm *.o lire 
