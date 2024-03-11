# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

2c: 2c.o utils_v1.o
	cc $(CFLAGS) -o 2c 2c.o utils_v1.o

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

2c.o: 2c.c
	cc $(CFLAGS) -c 2c.c

clean:
	rm *.o
	rm 2c 
