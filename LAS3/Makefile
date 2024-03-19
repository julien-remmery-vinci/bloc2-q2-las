# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

3b2: 3b2.o utils_v1.o
	cc $(CFLAGS) -o 3b2 3b2.o utils_v1.o

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

3b2.o: 3b2.c
	cc $(CFLAGS) -c 3b2.c

clean:
	rm *.o
	rm 3b2 
