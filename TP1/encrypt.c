#include <stdlib.h>
#include <stdio.h>
#include "crypt.h"
#include "utils_v1.h"

int main(int argc, char const *argv[])
{
	printf("Entrer un mot à crypter\n");
	char* word = readLine();
	char* encryptedWord = encrypt(word);
	printf("%s\n", encryptedWord);
}