#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cryptMorse.h"
#include "utils_v1.h"

#define TAB_LENGTH 26
#define LETTER_SEP 1
#define WORD_SEP 3
#define MAX_CRYPT_LENGTH 5

static char letters[TAB_LENGTH] = 
{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

static char* morseTab[TAB_LENGTH] =
{
".-", "-..." , "-.-." ,"-.."  ,"."    , 
"..-." ,"--."  ,"...." ,".."   ,".---" ,
"-.-"  , ".-.." , "--"   , "-."   ,  "---"  ,
 ".--." , "--.-" , ".-."  , "..."  ,  "-"   ,
 "..-"  , "...-" , ".--"  , "-..-" ,  "-.--" ,
"--.."
};

char findLetter(char* encrypted){
	for (int i = 0; i < TAB_LENGTH; ++i)
		if(strcmp(encrypted, morseTab[i]) == 0)
			return letters[i];
	return '0';
}

int getCryptLength(char* message){
	for (int i=0; i<strlen(message); i++)
      if (message[i] == ' ')
         return i;
   return -1;
}

char* encryptMorse(char* message){
	char* encrypted = (char*) malloc(1*sizeof(char));
	if(encrypted == NULL) return NULL;
	int wordLength = strlen(message);
	int encryptedLength = 0;
	int i = 0;
	while(i < wordLength){
		char c = message[i];
		if(c != ' '){
			char* crypt = morseTab[c-'A'];
			int cryptLength = strlen(crypt);
			encrypted = realloc(encrypted, (encryptedLength+cryptLength+LETTER_SEP)*sizeof(char));
			strcat(encrypted, " ");
			strcat(encrypted, crypt);
			encryptedLength += cryptLength+LETTER_SEP;
		}
		else{
			encrypted = realloc(encrypted, (encryptedLength+WORD_SEP)*sizeof(char));
			strcat(encrypted, "  ");
			encryptedLength += 2;
		}
		i++;
	}
	return encrypted;
}

char* decryptMorse(char* message){
	char code[MAX_CRYPT_LENGTH];
	char* decrypted = (char*) malloc(strlen(message)*sizeof(char));
	if(decrypted == NULL) return NULL;
	int indice = 0;
	char* ptr = message;
	while(*ptr != '\0'){
		if(*ptr == ' '){
			if(*(ptr+1) == ' '){
				decrypted[indice] = ' ';
				indice++;
				ptr += 2;
			}else{
				ptr++;
			}
		}else{
			int offset = getCryptLength(ptr);
			if (offset == -1) {  // fin de la chaîne msg
				strcpy(code, ptr);
				ptr += strlen(ptr);
			}
			else {
				strncpy(code, ptr, offset);
				code[offset] = '\0';
				ptr += offset+1;
			}

			int i = 0;
			while (morseTab[i] != NULL) {
				if (strcmp(code, morseTab[i]) == 0) {
				   decrypted[indice] = i + 'A';
				   indice++;
				   break;
				}
				i++;
			}
		}
	}
	return decrypted;
}
