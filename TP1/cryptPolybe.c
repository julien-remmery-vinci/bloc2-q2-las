#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cryptPolybe.h"

#define TAB_LENGTH 8

static char square[8][8] =
{{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
{'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
{'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
{'Y', 'Z', '0', '1', '2', '3', '4', '5'},
{'6', '7', '8', '9', ' ', '!', '"', '#'},
{'$', '%', '&', '\'', '(', ')', '*', '+'},
{',', '-', '.', '/', ':', ';', '<', '='},
{'>', '?', '@', '[', '\\', ']', '^', '_'}};

char* findIndex(char c){
	char* returned = (char*) malloc(3*sizeof(char));
	for(int i = 0 ; i < TAB_LENGTH ; i++)
		for(int j = 0 ; j < TAB_LENGTH ; j++)
			if(square[i][j] == toupper(c)){
				returned[0] = i+'0';
				returned[1] = j+'0';
				returned[2] = '\0';
				return returned;
			}
	free(returned);
	return NULL;
}

char findChar(char c1, char c2){
	char returned = square[(int)c1][(int)c2];
	return returned;
}

char* encryptPolybe(char* message){
	char* encrypted = (char*) malloc((strlen(message)*2+1)*sizeof(char));
	for(int i = 0 ; i < strlen(message) ; i++){
		char* encryptedWord = findIndex(message[i]);
		strcat(encrypted, encryptedWord);
		free(encryptedWord);
	}
	return encrypted;
}

char* decryptPolybe(char* message){
	char* decrypted = (char*) malloc((strlen(message)/2)*sizeof(char));
	int size = 0;
	for(int i = 0 ; i < strlen(message) ; i+=2){
		decrypted[size] = findChar(message[i], message[i+1]);
	}
	return decrypted;
}