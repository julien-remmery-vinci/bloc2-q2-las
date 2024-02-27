# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

secretAgent: secretAgent.o crypt.o cryptPolybe.o cryptMorse.o utils_v1.o
	cc $(CFLAGS) -o secretAgent secretAgent.o crypt.o cryptPolybe.o cryptMorse.o utils_v1.o

crypt.o: crypt.c
	cc $(CFLAGS) -c crypt.c

cryptPolybe.o: cryptPolybe.c
	cc $(CFLAGS) -c cryptPolybe.c

cryptMorse.o: cryptMorse.c
	cc $(CFLAGS) -c cryptMorse.c

utils_v1.o: utils_v1.c
	cc $(CFLAGS) -c utils_v1.c

secretAgent.o: secretAgent.c
	cc $(CFLAGS) -c secretAgent.c

clean:
	rm *.o secretAgent 
