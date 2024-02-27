# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

# Linker
lireEtEcrire : lireEtEcrire.o utils_v1.o
	cc $(CFLAGS) -o lireEtEcrire lireEtEcrire.o utils_v1.o

# Compilation
utils_v1.o : utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

lireEtEcrire.o : lireEtEcrire.c
	cc $(CFLAGS) -c lireEtEcrire.c

clean :
	rm *.o lireEtEcrire 
