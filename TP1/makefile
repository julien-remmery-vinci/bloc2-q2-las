make:
	cc -g makegen.c
	./a.out secretAgent.c
	cat Makefile

biblio:
	cc -g makegen.c
	./a.out testEcriture.c testLecture.c
	cat Makefile

playlist:
	cc -g makegen.c
	./a.out testplaylist.c
	cat Makefile	
makegen:
	cc -o makegen makegen.c
	sudo mv makegen /usr/bin

clean:
	rm Makefile ./a.out
