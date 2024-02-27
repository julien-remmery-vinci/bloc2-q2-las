CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all : mainbiblio

# Edition de liens
mainbiblio : mainBiblio.o utils_v1.o biblio.o
	cc $(CFLAGS) -o biblio mainBiblio.o utils_v1.o biblio.o

# Compilation
biblio.o : biblio.c
	cc $(CFLAGS) -c biblio.c

utils_v1.o : utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

mainbiblio.o : mainBiblio.c
	cc $(CFLAGS) -c mainbiblio.c

# Nettoyage
clean :
	rm *.o
	rm mainbiblio