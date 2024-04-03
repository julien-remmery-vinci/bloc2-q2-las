#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils_v1.h"
#include "ipcconfig.h"

volatile sig_atomic_t sem_id = 0;
volatile sig_atomic_t sem_id2 = 0;
volatile sig_atomic_t shm_id = 0;

int main(int argc, char const *argv[])
{
	sem_id = sem_get(SEM_KEY, 1);
	sem_id2 = sem_get(SEM_KEY2, 1);
	shm_id = sshmget(KEY, sizeof(char)*NB_CHARS, 0);
	char* z = sshmat(shm_id);

	sem_down0(sem_id);
	char upper[NB_CHARS] = {0};
	for (int i = 0; i < NB_CHARS; ++i)
		upper[i] = toupper(z[i]);
	strcpy(z, upper);
	sem_up0(sem_id2);
}