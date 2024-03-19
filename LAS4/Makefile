# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all: 41a 41b 

41a: 41a.o utils_v1.o
	cc $(CFLAGS) -o 41a 41a.o utils_v1.o

41b: 41b.o utils_v1.o
	cc $(CFLAGS) -o 41b 41b.o utils_v1.o

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

41a.o: 41a.c
	cc $(CFLAGS) -c 41a.c

41b.o: 41b.c
	cc $(CFLAGS) -c 41b.c

clean:
	rm *.o
	rm 41a 41b 
