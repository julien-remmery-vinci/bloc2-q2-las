#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "biblio.h"
#include "utils_v1.h"

// Définition de variable globale pour fonctions str2genre et genre2str

static char* lesGenres[] = {"Bande dessinée", "Poésie", "Théâtre",
                            "Roman", "Roman historique", "Littérature française",
                            "Littérature étrangère", "Sciences", "Informatique",
                            "Science-fiction", "Santé", "Histoire", NULL};


// Implémentation des fonctions

bool lireLivre (struct Livre *l) {
    // buffer de lecture
   char ligne[MAX_TITRE+2];

   // lecture du titre
   if (readLimitedLine(ligne,MAX_TITRE+2) <= 0) return false;
   strcpy(l->titre, ligne);
   // OU: readLimitedLine(l->titre,MAX_TITRE+2)  
   // mais lire directement dans les chaînes de la structure Livre 
   // implique que la taille des champs devrait être augmentée de +1 
   // pour la lecture de '\n'

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

   //getchar();   // lecture de ligne vide effectuée dans le programme appelant

   return true;
}

/*
// Variante sans la variable globale lesGenres
enum Genre str2genre (char *s) {
	if (strcmp(s,"Bande dessinée") == 0) return BD;
	if (!strcmp(s,"Poésie")) return PO;
	if (!strcmp(s,"Théâtre")) return TH;
	if (!strcmp(s,"Roman")) return RO;
	if (!strcmp(s,"Roman historique")) return RH;
	if (!strcmp(s,"Littérature française")) return LF;
	if (!strcmp(s,"Littérature étrangère")) return LE;
	if (!strcmp(s,"Sciences")) return SC;
	if (!strcmp(s,"Informatique")) return IN;
	if (!strcmp(s,"Science-fiction")) return SF;
	if (!strcmp(s,"Santé")) return SA;
	if (!strcmp(s,"Histoire")) return HI;
	return -1;
}
*/

enum Genre str2genre (char *s) {
   for (enum Genre g = 0; g < GENRES_NUM; g++){
      if (!strcmp(s, lesGenres[g])){
         return g;
      } 
   }
   /* 
     // OU en arithmétique des pointeurs:
     enum Genre g = 0;  // = BD
     for (char** ptr = lesGenres; *ptr != NULL; ptr++, g++){
        if (!strcmp(s, *ptr)){
           return g;
        }
     }
   */
   return -1;
}

/*
// Variante sans la variable globale lesGenres
char* genre2str (enum Genre g) {
	switch (g) {
		case BD: return "Bande dessinée";
		case PO: return "Poésie";
		case TH: return "Théâtre";
		case RO: return "Roman";
		case RH: return "Roman historique";
		case LF: return "Littérature française";
		case LE: return "Littérature étrangère";
		case SC: return "Sciences";
		case IN: return "Informatique";
		case SF: return "Science-fiction";
		case SA: return "Santé";
		case HI: return "Histoire";
		default: return NULL;
	}
}
*/

// VARIANTE:

char* genre2str (enum Genre g) {
   int nbGenres = sizeof(lesGenres)/sizeof(char*) - 1;  // -1 pour ne pas compter NULL
   if (g < 0 || g >= nbGenres)
      return NULL;
   return lesGenres[g];
}

char* livre2str (char *s, const struct Livre l) {
   sprintf(s, "%-40s %-20s %10ld  %-20s %5d  %s", 
           l.titre, l.auteur, l.isbn, l.editeur, l.an, genre2str(l.genre));
   return s;
}

void afficherBib (const struct Livre* bib, int t) {
   char ligne[MAX_LIGNE_LIVRE];
   printf("Voici ma bib de %d livres:\n", t);
   for (int i=0; i<t; i++) {
      printf("\t%s\n", livre2str(ligne, bib[i]));
   }
   /*
     // OU en arithmétique des pointeurs:
     for (struct Livre *ptr = bib; ptr < bib+t; ptr++) {
        printf("\t%s\n", livre2str(ligne, *ptr));
     }
   */
   printf("---------------------------\n");
}

// Cette fonction est similaire à la fonction ajouterTable() du TP7-ex5 (BINV2011)
bool ajouterLivre (struct Livre **bib, struct Livre l, int *nbreL, int *taille) {
   if (*taille == 0){
      if ((*bib = (struct Livre*)malloc((*taille=3)*sizeof(struct Livre))) == NULL){
         perror("Malloc");
         return false;
      }
   } else if (*taille == *nbreL){
      *taille *= 2;
      if ((*bib = (struct Livre*)realloc(*bib, *taille * sizeof(struct Livre))) == NULL){
         perror("Realloc");
         return false;
      }
   }
   (*bib)[*nbreL] = l;  // copie bit à bit d'une structure Livre!
   (*nbreL)++;
   return true;
}

// TP4

int ecrireFichier(FILE* f, struct Livre* t, int nbreL) {
   return fwrite(t, sizeof(struct Livre), nbreL, f);
}

bool lireFichier(struct Livre** t, FILE* f, int* nbreL, int* taille) {
   struct Livre tmp[MAX_NB_LIVRES];
   size_t nread = MAX_NB_LIVRES;
   while (nread == MAX_NB_LIVRES) {
      nread = fread(tmp, sizeof(struct Livre), MAX_NB_LIVRES, f);
      for (int i = 0; i < nread; ++i)
      {
         ajouterLivre(t, tmp[i], nbreL, taille);
      }
      if(ferror(f) != 0) return false;
   }
   return true;
}

/// Bonus 3: qsort

// Cette signature provient de la compatibilité avec qsort.
// Une explication sur la généricité en C est disponible sur 
//    https://youtu.be/xQBefPZw2jA
int comparerLivre (const struct Livre *a, const struct Livre *b) {
   return a->an - b->an;
}

