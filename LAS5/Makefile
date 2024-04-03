# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all: 51a 51b 52 

51a: 51a.o utils_v1.o
	cc $(CFLAGS) -o 51a 51a.o utils_v1.o

51b: 51b.o utils_v1.o
	cc $(CFLAGS) -o 51b 51b.o utils_v1.o

52: 52.o utils_v1.o
	cc $(CFLAGS) -o 52 52.o utils_v1.o

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

51a.o: 51a.c
	cc $(CFLAGS) -c 51a.c

51b.o: 51b.c
	cc $(CFLAGS) -c 51b.c

52.o: 52.c
	cc $(CFLAGS) -c 52.c

clean:
	rm *.o
	rm 51a 51b 52 
