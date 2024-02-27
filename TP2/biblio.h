#ifndef _BIBLIO_H_
#define _BIBLIO_H_

#include <stdbool.h>

#define MAX_TITRE 128
#define MAX_AUTEUR 80
#define MAX_EDITEUR 50
#define MAX_LIGNE MAX_TITRE+MAX_AUTEUR+MAX_EDITEUR+50


enum Genre {
	BANDE_DESSINEE,
	POESIE,
	THEATRE,
	ROMAN,
	ROMAN_HISTORIQUE,
	LITTERATURE_FRANCAISE,
	LITTERATURE_ETRANGERE,
	SCIENCES,
	INFORMATIQUE,
	SCIENCES_FICTION,
	SANTE,
	HISTOIRE,
	GENRES_NUM
};

struct Livre {
	char titre[MAX_TITRE+1];
	char auteur[MAX_AUTEUR+1];
	long isbn;
	char editeur[MAX_EDITEUR+1];
	int an;
	enum Genre genre;
};

bool lireLivre(struct Livre* l);
enum Genre str2genre(char* genre);
char* genre2str(enum Genre genre);
char* livre2str(char* s, struct Livre livre);
void afficherBib(struct Livre* livres, int nbLivres);
bool ajouterLivre(struct Livre** livres, struct Livre l, int* nbLivres, int sz);

#endif