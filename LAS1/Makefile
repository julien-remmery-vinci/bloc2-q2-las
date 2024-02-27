# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all: compfwrite compwrite 

compfwrite: compfwrite.o
	cc $(CFLAGS) -o compfwrite compfwrite.o

compwrite: compwrite.o utils_v1.o
	cc $(CFLAGS) -o compwrite compwrite.o utils_v1.o

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

compwrite.o: compwrite.c
	cc $(CFLAGS) -c compwrite.c

clean:
	rm *.o compwrite 
