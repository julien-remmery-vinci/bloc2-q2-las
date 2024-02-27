#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils_v1.h"
#include "biblio.h"

static char* genres[] = {
	"Bande dessinée",
	"Poésie",
	"Théatre",
	"Roman",
	"Roman historique",
	"Littérature française",
	"Littérature étrangère",
	"Sciences",
	"Informatique",
	"Sciences fiction",
	"Santé",
	"Histoire",
	NULL
};

bool lireLivre (struct Livre *l) {
	// buffer de lecture
	char ligne[MAX_TITRE+2];

	// lecture du titre
	if (readLimitedLine(ligne,MAX_TITRE+2) <= 0) return false;
	strcpy(l->titre, ligne);

	// lecture de l'auteur
	if (readLimitedLine(ligne,MAX_AUTEUR+2) <= 0) return false;
	strcpy(l->auteur, ligne);

	// lecture de l'isbn
	if (scanf("%ld\n",&l->isbn) != 1) return false;

	// lecture de l'éditeur
	if (readLimitedLine(ligne,MAX_EDITEUR+2) <= 0) return false;
	strcpy(l->editeur, ligne);

	// lecture de l'année
	if (scanf("%d\n",&l->an) != 1) return false;

	// lecture du genre
	if (readLimitedLine(ligne,MAX_TITRE+2) <= 0) return false;
	if ((l->genre = str2genre(ligne)) == -1) return false;
	return true;
}

enum Genre str2genre(char* genre){
	for (enum Genre g = 0; g < GENRES_NUM; ++g)
		if(!strcmp(genre, genres[g]))
			return g;
	return -1;
}

char* genre2str(enum Genre genre){
	int nbGenre = sizeof(genres)/sizeof(char*) -1;
	if(genre < 0 || genre >= nbGenre) return NULL;
	return genres[genre];
}

char* livre2str(char* s, const struct Livre livre){
	sprintf(s, "%-40s %-20s %10ld %-20s %5d %s", livre.titre, livre.auteur, livre.isbn, livre.editeur, livre.an, genre2str(livre.genre));
	return s;
}

void afficherBib(struct Livre* livres, int nbLivres){
	char livre[MAX_LIGNE];
	printf("Ma bibliothèque :\n");
	for (int i = 0; i < nbLivres; ++i)
	{
		livre2str(livre, livres[i]);
		printf("%s\n", livre);
	}
}

bool ajouterLivre(struct Livre** livres, struct Livre l, int* nbLivres, int sz){
	if((*nbLivres) == sz) return false;
	if(livres == NULL){
		*livres = (struct Livre*) malloc(sz*sizeof(struct Livre));
		if(*livres == NULL) return NULL;
	}
	livres[*nbLivres] = malloc(sizeof(struct Livre));
	if(livres[*nbLivres] == NULL) return false;
	(*livres)[*nbLivres] = l;
	(*nbLivres)++;
	return true;
}