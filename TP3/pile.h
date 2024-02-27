#ifndef _NPI_H_
#define _NPI_H_

#include <stdbool.h>

typedef struct Noeud {
	int valeur;
	struct Noeud* suivant;
} Noeud;

typedef Noeud* Pile;

Pile initPile ();
bool pileVide (Pile);
bool push (Pile*, int);
int pop (Pile*);
void viderPile (Pile*);
void afficherPile (Pile);

#endif