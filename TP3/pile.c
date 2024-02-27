#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

Pile initPile (){
	return NULL;
}

bool pileVide (Pile p){
	if(p == NULL) return true;
	return false;
}

bool push (Pile* p, int v){
	struct Noeud* n = (Noeud*) malloc(sizeof(Noeud));
	if(n == NULL) return false;
	n->valeur = v;
	n->suivant = (*p);
	*p = n;
	return true;
}

int pop (Pile* p){
	struct Noeud* n = *p;
	*p = (*p)->suivant;
	int val = n->valeur;
	free(n);
	return val;
}

void viderPile (Pile* p){
	struct Noeud* n = *p;
	struct Noeud* ni;
	while(n != NULL){
		ni = n->suivant;
		free(n);
		n = ni;
	}
	*p = NULL;
}

void afficherPile (Pile p){
	Noeud *n = p;
	for (int i = 0; i < 3; ++i)
	{
		printf("%d\n", n->valeur);
		n = n->suivant;
	}
}