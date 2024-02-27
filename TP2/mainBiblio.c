#include <stdlib.h>
#include <stdio.h>
#include "biblio.h"

#define MAX_LIVRES 10

int main(int argc, char const *argv[])
{
	struct Livre* livres;
	struct Livre l;
	int nbLivres = 0;
	while(lireLivre(&l)){
		getchar();
		ajouterLivre(&livres, l, &nbLivres, MAX_LIVRES);
	}
	afficherBib(livres, nbLivres);
	free(livres);
}