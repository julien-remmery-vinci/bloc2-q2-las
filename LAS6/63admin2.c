#include <stdlib.h>
#include <string.h>
#include "utils_v1.h"
#include "ipcconfig.h"

int main(int argc, char const *argv[])
{
	if (argc != 1) {
		if (strcmp("-c", argv[1]) == 0) {
			printf("Initialisation de la mémoire partagée et de la sémaphore\n");
			sem_create(SEM_KEY, 1, PERM, 0);
			sem_create(SEM_KEY2, 1, PERM, 0);
			sshmget(KEY, sizeof(char)*NB_CHARS, IPC_CREAT | PERM);
		}
		else if (strcmp("-d", argv[1]) == 0) {
			printf("Destruction de la mémoire partagée et de la sémaphore\n");
			sem_delete(sem_get(SEM_KEY, 1));
			sem_delete(sem_get(SEM_KEY2, 1));
			sshmdelete(sshmget(KEY, sizeof(char)*NB_CHARS, 0));
		}
		else {
			printf("Wrong option!\n");
		}
	}
	else {
		printf("No option provided!\n");
	}
}