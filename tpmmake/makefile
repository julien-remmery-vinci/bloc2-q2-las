# made using makegen by julien.r
CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

makegen: makegen.o makegen_utils.o 
	gcc $(CFLAGS) -o makegen makegen.o makegen_utils.o 

makegen_utils.o: makegen_utils.c makegen_utils.h
	gcc $(CFLAGS) -c makegen_utils.c

makegen.o: makegen.c makegen_utils.h 
	gcc $(CFLAGS) -c makegen.c

clean:
	rm *.o
	rm makegen
