#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils_v1.h"

#define MAX_SIG 7

volatile sig_atomic_t nbSig;

void sigusr_handler(int signum) {
	char* str = "signal SIGUSR1 recu !\n";
	swrite(1, str, strlen(str)*sizeof(char));
	nbSig++;
	if(nbSig == MAX_SIG)
		_exit(1);
}

void sigchild_handler(int signum) {
	char* str = "hajou et hadjera sont mortes je n'ai plus de raison de vivre je m'en vais salut les enfants\n";
	swrite(1, str, strlen(str)*sizeof(char));
	_exit(1);
}

int main(int argc, char const *argv[])
{
	ssigaction(SIGUSR1, sigusr_handler);
	ssigaction(SIGCHLD, sigchild_handler);

	int cid = sfork();
	if(cid > 0) {
		while(1) {
			skill(cid, SIGUSR1);
			sleep(1);
		}
	} else {
		while(1) {
			sleep(1);
		}
	}
}