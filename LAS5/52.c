#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "utils_v1.h"

volatile sig_atomic_t nbReceived = 0;
volatile sig_atomic_t nbSent = 0;
volatile sig_atomic_t cid = 0;
volatile sig_atomic_t end = 0;

void sigusr1(int sig){
	nbReceived++;  
}

void sigusr2(int sig){
	end = 1;
}

void sigalarm_handler(int sig){
	end = 1;
	skill(cid, SIGUSR2);
}

int main(int argc, char const *argv[])
{
	sigset_t set;
	ssigemptyset(&set);
	ssigaddset(&set, SIGUSR1);
	ssigprocmask(SIG_BLOCK, &set, NULL);

	ssigaction(SIGUSR1, sigusr1);
	ssigaction(SIGUSR2, sigusr2);
	ssigaction(SIGALRM, sigalarm_handler);

	ssigdelset(&set,SIGUSR1);

	cid = sfork();
	if(cid > 0){
		alarm(5);
		while(end != 1){
			skill(cid, SIGUSR1);
			nbSent++;
			sigsuspend(&set);
		}
		printf("Pere: nombre de signaux envoyées: %d, recus: %d\n", nbSent, nbReceived);
		swaitpid(cid, 0, 0);
	} else {
		while(end != 1){
			sigsuspend(&set);
			nbSent++;
			skill(getppid(), SIGUSR1);
		}
		printf("Fils: nombre de signaux envoyées: %d, recus: %d\n", nbSent, nbReceived);
	}
}