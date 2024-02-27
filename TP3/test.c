#include <stdio.h>
#include "pile.h"

int main(int argc, char const *argv[])
{
	int i;
	scanf("%d", &i);
	struct Noeud* n;
	push(&n, i);
	push(&n, 5);
	push(&n, 7);
	afficherPile(n);
}