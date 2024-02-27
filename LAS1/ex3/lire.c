#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

#include "utils_v1.h"

#define MAX_SIZE 11

int main(int argc, char const *argv[])
{
	int nbCharRd;
	do{
		char bufRd[MAX_SIZE];
		printf("Entrez une chaine de max %d caracteres:\n", MAX_SIZE-1);
		nbCharRd = read(0, bufRd, MAX_SIZE);
		while(bufRd[MAX_SIZE-1] != '\n' && nbCharRd == 11) {
			while(bufRd[0] != '\n') {
				read(0, bufRd, 1);
			}
			printf("Vous avez entré trop de caractères !\nEntrez une chaine de max %d caracteres:\n", MAX_SIZE-1);
			nbCharRd = read(0, bufRd, MAX_SIZE);
		}
		int nbCharWr = write(1, bufRd, nbCharRd);
		checkCond(nbCharWr != nbCharRd,"Error while writing");
	}while (nbCharRd > 0);
}