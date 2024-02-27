#include <stdlib.h>
#include <stdio.h>
#include "utils_v1.h"
#include "crypt.h"

int main(int argc, char const *argv[])
{
	printf("Entrer un mot à décrypter\n");
	char* encryptedWord = readLine();
	char* decryptedWord = decrypt(encryptedWord);
	printf("%s\n", decryptedWord);
}