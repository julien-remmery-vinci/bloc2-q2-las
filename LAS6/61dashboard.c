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
	int shm_id = sshmget(SEM_KEY, sizeof(int), 0);
	int* z = sshmat(shm_id);
	for (int i = 0; i < 12; i++)
	{
		printf("Dashboard: Valeur de *z = %d\n", *z);
		sleep(5);
	}
	sshmdt(z);
}