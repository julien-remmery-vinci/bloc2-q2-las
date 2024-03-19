# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

42: 42.o utils_v1.o
	cc $(CFLAGS) -o 42 42.o utils_v1.o

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

42.o: 42.c
	cc $(CFLAGS) -c 42.c

clean:
	rm *.o
	rm 42 
