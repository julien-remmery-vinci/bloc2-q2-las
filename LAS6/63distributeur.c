#include <stdlib.h>
#include "utils_v1.h"
#include "ipcconfig.h"

int main(int argc, char const *argv[])
{
	int sem_id = sem_get(SEM_KEY, 1);
	int shm_id = sshmget(KEY, sizeof(int)*2, 0);
	int* z = sshmat(shm_id);

	sem_down0(sem_id);
	(*z)++;
	sem_up0(sem_id);
	printf("Numéro de ticket: %d\n", *z);
	sshmdt(z);
}