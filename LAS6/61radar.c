#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include "utils_v1.h"
#include "ipcconfig.h"

int main(int argc, char const *argv[])
{
	int shm_id = sshmget(SEM_KEY, sizeof(int), IPC_CREAT | PERM);
	int* z = sshmat(shm_id);
	for (int i = 0; i < 20; i++)
	{
		int r = randomIntBetween(1, 100);
		*z = r;
		printf("Radar: Valeur de *z = %d\n", *z);
		sleep(3);
	}
	sshmdt(z);
}