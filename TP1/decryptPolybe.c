#include <stdlib.h>
#include "cryptPolybe.h"
#include "utils_v1.h"

int main(int argc, char const *argv[])
{
	printf("Entrer un mot à décrypter\n");
	char* encryptedWord = readLine();
	char* decryptedWord = decryptPolybe(encryptedWord);
	printf("Decrypted: %s\n", decryptedWord);
	free(encryptedWord);
	free(decryptedWord);
}