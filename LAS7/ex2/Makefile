CFLAGS=-D_DEFAULT_SOURCE -g -w -Werror

client: utils_v1.o client.o
	gcc $(CFLAGS) -o client client.o utils_v1.o

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c 

client.o: client.c
	gcc $(CFLAGS) -c client.c 

clean:
	rm -f *.o
	rm client
