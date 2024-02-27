#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "utils_v1.h"
#include "pile.h"

#define BUF_SIZE 257

bool erreurPileVide (Pile, char*);

// Programme principal

int main (int argc, char **argv){
   char ligne[BUF_SIZE];
   char message[BUF_SIZE];
   int n;
   int op1, op2, res;
   int erreur = false;

   Pile maPile = initPile();
   while (readLimitedLine(ligne,BUF_SIZE) != -1){
      printf("%s = ", ligne);
      n = strspn(ligne, " 0123456789+-*/\n");
      if (n != strlen(ligne)) {
         sprintf(message, "expression incorrecte en %c\n", ligne[n]);
         printError(message);
         continue;
      }
      erreur = false;
      for (int i=0; i<strlen(ligne) && !erreur; i++) {
         if (ligne[i] == ' ')
            continue;
         switch (ligne[i]) {
         case '+' : 
            if ((erreur = erreurPileVide(maPile, "pile vide: pas de seconde opérande...\n")))
               continue;
            op2 = pop(&maPile);
            if ((erreur = erreurPileVide(maPile, "pile vide: pas de première opérande...\n")))
               continue;
            op1 = pop(&maPile);
            res = op1 + op2;
            push(&maPile, res);
            break;
         case '-' : 
            if ((erreur = erreurPileVide(maPile, "pile vide: pas de seconde opérande...\n")))
               continue;
            op2 = pop(&maPile);
            if ((erreur = erreurPileVide(maPile, "pile vide: pas de première opérande...\n")))
               continue;
            op1 = pop(&maPile);
            res = op1 - op2;
            push(&maPile, res);
            break;
         case '*' : 
            if ((erreur = erreurPileVide(maPile, "pile vide: pas de seconde opérande...\n")))
               continue;
            op2 = pop(&maPile);
            if ((erreur = erreurPileVide(maPile, "pile vide: pas de première opérande...\n")))
               continue;
            op1 = pop(&maPile);
            res = op1 * op2;
            push(&maPile, res);
            break;
         case '/' : 
            if ((erreur = erreurPileVide(maPile, "pile vide: pas de seconde opérande...\n")))
               continue;
            op2 = pop(&maPile);
            if ((erreur = erreurPileVide(maPile, "pile vide: pas de première opérande...\n")))
               continue;
            op1 = pop(&maPile);
            if (op2 == 0){
               printError("division par 0\n");     
               viderPile(&maPile);
               erreur = true;
               continue;
            }
            res = op1 / op2;
            push(&maPile, res);
            break;
         default :  // traitement d'un chiffre
            n = ligne[i] - '0';
            push(&maPile,n);
            break;
         }  // end switch
      }  // end for
      if (erreur){
         continue;
      }
      if (pileVide(maPile)){
         printError("manque des operandes: pas de reponse\n");       
         continue;
      }
      res = pop(&maPile);
      if (!pileVide(maPile)){
         printError("trop d'operandes: expression incorrecte\n");        
         viderPile(&maPile);
         continue;
      }
        
      sprintf(message, "la reponse est : %d\n", res);
      printOk(message);
   }  // end while
}

/*************************************/

bool erreurPileVide (Pile maPile, char* msg) {
   if (pileVide(maPile)) {
      printError(msg);
      return true;
   }
   return false;
}
