#include <stdlib.h>
#include <unistd.h>
#include "utils_v1.h"

void display() {
	for (int i = 0; i < 3; ++i)
	{
		printf("Je suis le fils %d\n", getpid());
		sleep(1);
	}
}

int main(int argc, char const *argv[])
{
	pid_t cpid1 = fork_and_run0(display);
	pid_t cpid2 = fork_and_run0(display);

	swaitpid(cpid1, NULL, 0);
	swaitpid(cpid2, NULL, 0);
}