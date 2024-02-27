#include <stdio.h>

int main(int argc, char const *argv[])
{
	enum Couleur { ROUGE=10, VERT, BLEU };
	enum Couleur c = ROUGE;
	struct A {
		char taille[100];
	};
	struct B {
		int* taille;
	};
	struct A a;
	struct B b;
	printf("%ld\n", sizeof(a));
	printf("%ld\n", sizeof(b));
}