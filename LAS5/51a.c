#include <unistd.h>
#include <string.h>
#include "utils_v1.h"

static const char* const FILS_EN_VIE = "mon fils est toujours en vie\n";

void sigusr_handler(int signum){
	swrite(1, FILS_EN_VIE, strlen(FILS_EN_VIE));
	alarm(8);
}

static const char* const FILS_MORT = "mon fils est down\n";

void sigalarm_dad(int signum){
	swrite(1, FILS_MORT, strlen(FILS_MORT));
	_exit(5);
}

void sigalarm_child(int signum){
	skill(getppid(), SIGUSR1);
	alarm(3);
}

int main(int argc, char const *argv[])
{
	sigset_t set;
	ssigemptyset(&set);
	ssigaddset(&set, SIGUSR1);
	ssigaddset(&set, SIGALRM);
	ssigprocmask(SIG_BLOCK, &set, NULL);
	pid_t childID = fork();
	// PERE
	if (childID > 0) {
		/* lancement d'un compte à rebours de 8 secondes */
		//TODO
		ssigaction(SIGUSR1, sigusr_handler);
		ssigaction(SIGALRM, sigalarm_dad);
		ssigprocmask(SIG_UNBLOCK, &set, NULL);
		alarm(8);
		while (true) {
			sleep(1);
		}
	}
	// FILS
	else {
		/* lancement d'un compte à rebours de 3 secondes */
		//TODO
		ssigaction(SIGALRM, sigalarm_child);
		ssigprocmask(SIG_UNBLOCK, &set, NULL);

		alarm(3);
		while (true) {
			sleep(1);
		}
	}	
}