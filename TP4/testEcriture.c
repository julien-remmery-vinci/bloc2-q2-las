#include <stdio.h>
#include <stdlib.h>

#include "biblio.h"

int main(int argc, char const *argv[])
{
	struct Livre* livres;
	struct Livre l;
	int nbLivres = 0;
	int taille = 0;
	while(lireLivre(&l)){
		getchar();
		ajouterLivre(&livres, l, &nbLivres, &taille);
	}

	FILE* fout = fopen(argv[1], "wb");
	if(fout == NULL) {
		printf("Error : could not open file\n");
		exit(1);
	}

	if(!ecrireFichier(fout, livres, nbLivres)){
		printf("Error : error while writing in file\n");
		exit(1);
	}
}