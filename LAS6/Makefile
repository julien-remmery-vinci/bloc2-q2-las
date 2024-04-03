# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all: 63client 63serveur 63admin2 

63client: 63client.o utils_v1.o ipcconfig.h
	cc $(CFLAGS) -o 63client 63client.o utils_v1.o

63serveur: 63serveur.o utils_v1.o ipcconfig.h
	cc $(CFLAGS) -o 63serveur 63serveur.o utils_v1.o

63admin2: 63admin2.o utils_v1.o ipcconfig.h
	cc $(CFLAGS) -o 63admin2 63admin2.o utils_v1.o

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

63client.o: 63client.c
	cc $(CFLAGS) -c 63client.c

63serveur.o: 63serveur.c
	cc $(CFLAGS) -c 63serveur.c

63admin2.o: 63admin2.c
	cc $(CFLAGS) -c 63admin2.c

clean:
	rm *.o
	rm 63client 63serveur 63admin2 
