#include <stdlib.h>
#include "crypt.h"
#include "cryptPolybe.h"
#include "cryptMorse.h"
#include "utils_v1.h"

int main(int argc, char const *argv[])
{
	int choix;
	char* word;
	char* encryptedWord;
	char* decryptedWord;
	do{
		printf("1. Cryptage\n2. Décryptage\n0. Quitter\n");
		scanf("%d", &choix);
		getchar();
		switch(choix){
			case 0:
				free(word);
				free(encryptedWord);
				free(decryptedWord);
				exit(0);
			case 1:
				printf("1. ROT13\n2. Polybe\n3. Morse\n");
				scanf("%d", &choix);
				getchar();
				switch(choix){
					case 1:
						printf("Entrer un mot à crypter: \n");
						word = readLine();
						encryptedWord = encrypt(word);
						printf("Encrypted: %s\n", encryptedWord);
						break;
					case 2:
						printf("Entrer un mot à crypter: \n");
						word = readLine();
						encryptedWord = encryptPolybe(word);
						printf("Encrypted: %s\n", encryptedWord);
						break;
					case 3:
						printf("Entrer un mot à crypter: \n");
						word = readLine();
						encryptedWord = encryptMorse(word);
						printf("Encrypted: %s\n", encryptedWord);
						break;
					default:
						break;
				}
				break;
			case 2:
				printf("1. ROT13\n2. Polybe\n3. Morse");
				scanf("%d", &choix);
				getchar();
				switch(choix){
					case 1:
						printf("Entrer un mot à décrypter: \n");
						encryptedWord = readLine();
						decryptedWord = decrypt(encryptedWord);
						printf("Decrypted: %s\n", decryptedWord);
						break;
					case 2:
						printf("Entrer un mot à décrypter: \n");
						encryptedWord = readLine();
						decryptedWord = decryptPolybe(encryptedWord);
						printf("Decrypted: %s\n", decryptedWord);
						break;
					case 3:
						printf("Entrer un mot à décrypter: \n");
						encryptedWord = readLine();
						decryptedWord = decryptMorse(encryptedWord);
						printf("Decrypted: %s\n", decryptedWord);
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}while(choix != 0);
}