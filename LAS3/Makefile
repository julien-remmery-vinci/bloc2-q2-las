# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

3c: 3c.o utils_v1.o
	cc $(CFLAGS) -o 3c 3c.o utils_v1.o

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

3c.o: 3c.c
	cc $(CFLAGS) -c 3c.c

clean:
	rm *.o
	rm 3c 
