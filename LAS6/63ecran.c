#include <stdlib.h>
#include <unistd.h>
#include "utils_v1.h"
#include "ipcconfig.h"

volatile sig_atomic_t sem_id = 0;
volatile sig_atomic_t shm_id = 0;

void sigint_handler(int signum) {
	sem_up0(sem_id);
	int* z = sshmat(shm_id);
	sshmdt(z);
	_exit(1);
}

int main(int argc, char const *argv[])
{
	ssigaction(SIGINT, sigint_handler);
	sem_id = sem_get(SEM_KEY, 1);
	shm_id = sshmget(KEY, sizeof(int)*2, 0);
	int* z = sshmat(shm_id);
	int* x = z + 1;

	sem_down0(sem_id);
	do {
		(*x)++;
		printf("Ticket appelé: %d\n", *x);
		sleep(1);
	} while(*z != *x);
	printf("Plus de tickets à appeler !\n");
	sem_up0(sem_id);
	sshmdt(z);
}