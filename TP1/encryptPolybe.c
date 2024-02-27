#include <string.h>
#include <stdlib.h>
#include "cryptPolybe.h"
#include "utils_v1.h"

int main(int argc, char const *argv[])
{
	printf("Entrer un mot à crypter\n");
	char* word = readLine();
	char* encryptedWord = encryptPolybe(word);
	printf("Encrypted: %s\n", encryptedWord);
	free(word);
	free(encryptedWord);
}