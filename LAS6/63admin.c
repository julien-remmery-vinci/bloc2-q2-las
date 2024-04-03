#include <stdlib.h>
#include <string.h>
#include "utils_v1.h"
#include "ipcconfig.h"

int main(int argc, char const *argv[])
{
	if (argc != 1) {
		if (strcmp("-c", argv[1]) == 0) {
			printf("Initialisation de la mémoire partagée et de la sémaphore\n");
			sem_create(SEM_KEY, 1, PERM, 2);
			sshmget(KEY, sizeof(int)*2, IPC_CREAT | PERM);
		}
		else if (strcmp("-d", argv[1]) == 0) {
			printf("Destruction de la mémoire partagée et de la sémaphore\n");
			sem_delete(sem_get(SEM_KEY, 1));
			sshmdelete(sshmget(KEY, sizeof(int)*2, 0));
		}
		else {
			printf("Wrong option!\n");
		}
	}
	else {
		printf("No option provided!\n");
	}
}