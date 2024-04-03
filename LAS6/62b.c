#include <stdlib.h>
#include <unistd.h>
#include "utils_v1.h"

#define SEM_KEY 666
#define PERM 0666

void display() {
	int sem_id = sem_get(SEM_KEY, 1);
	for (int i = 0; i < 3; ++i)
	{
		sem_down0(sem_id);
		printf("Je suis le fils %d\n", getpid());
		sem_up0(sem_id);
		sleep(1);
	}
}

int main(int argc, char const *argv[])
{
	int sem_id = sem_create(SEM_KEY, 1, PERM, 1);

	pid_t cpid1 = fork_and_run0(display);
	pid_t cpid2 = fork_and_run0(display);

	swaitpid(cpid1, NULL, 0);
	swaitpid(cpid2, NULL, 0);

	sem_delete(sem_id);
}