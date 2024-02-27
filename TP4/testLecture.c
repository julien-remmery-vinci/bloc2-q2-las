#include <stdlib.h>
#include <stdio.h>

#include "biblio.h"

int main(int argc, char const *argv[])
{
	FILE* fin = fopen(argv[1], "rb");
	if(fin == NULL) {
		printf("Error : could not open file\n");
		exit(1);
	}

	struct Livre* livres;
	int nbLivres = 0;
	int taille = 0;
	lireFichier(&livres, fin, &nbLivres, &taille);

	afficherBib(livres, nbLivres);
}