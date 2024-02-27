#include <stdlib.h>
#include <stdio.h>

#include "biblio.h"

int cmp (const void *l1, const void *l2) {
   return comparerLivre((struct Livre*) l1, (struct Livre*) l2);
}

int main(int argc, char const *argv[])
{
	if(argc == 1 || argc > 3) {

	}
	FILE* fin;
	FILE* fout;
	struct Livre* livres;
	int nbLivres = 0;
	int taille = 0;

	if(argc > 2){
		fin = fopen(argv[1], "rb");
		if(fin == NULL) {
			fprintf(stderr, "Error : could not open write file\n");
			exit(10);
		}
		if(!lireFichier(&livres, fin, &nbLivres, &taille)) {
			fprintf(stderr, "Error : error while reading in file\n");
			exit(13);
		}
		fclose(fin);
		if(livres == NULL) {
			fprintf(stderr, "Error : malloc error\n");
			exit(20);
		}

		afficherBib(livres, nbLivres);
		qsort(livres, nbLivres, sizeof(struct Livre), cmp);
		afficherBib(livres, nbLivres);
		fout = fopen(argv[2], "wb");

		if(fout == NULL) {
			fprintf(stderr, "Error : could not open output file\n");
			exit(11);
		}

		if(!ecrireFichier(fout, livres, nbLivres)) {
			fprintf(stderr, "Error : error while writing in file\n");
			exit(12);
		}
	}
	else{
		fout = fopen("testOut", "wb");
		if(fout == NULL) {
			fprintf(stderr, "Error : could not open output file\n");
			exit(11);
		}
	}
	struct Livre l;
	while(lireLivre(&l)){
		getchar();
		ajouterLivre(&livres, l, &nbLivres, &taille);
	}
	if(!ecrireFichier(fout, livres, nbLivres)){
		fprintf(stderr, "Error : error while writing in file\n");
		exit(1);
	}
	afficherBib(livres, nbLivres);
	qsort(livres, nbLivres, sizeof(struct Livre), cmp);
	afficherBib(livres, nbLivres);

	fclose(fout);
	free(livres);
}