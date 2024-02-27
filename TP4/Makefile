# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all : testEcriture testLecture 

# Linker
testEcriture : testEcriture.o biblio.o utils_v1.o
	cc $(CFLAGS) -o testEcriture testEcriture.o biblio.o utils_v1.o

testLecture : testLecture.o biblio.o utils_v1.o
	cc $(CFLAGS) -o testLecture testLecture.o biblio.o utils_v1.o

# Compilation
biblio.o : biblio.c
	cc $(CFLAGS) -c biblio.c

utils_v1.o : utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

testEcriture.o : testEcriture.c
	cc $(CFLAGS) -c testEcriture.c

testLecture.o : testLecture.c
	cc $(CFLAGS) -c testLecture.c

clean :
	rm *.o testEcriture testLecture 
