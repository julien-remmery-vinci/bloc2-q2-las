#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils_v1.h"

void sighandler(int sig) {
	char* str = strsignal(sig);
	swrite(1, str, strlen(str)*sizeof(char));
}

int main(int argc, char const *argv[])
{
	for (int i = 1; i <= 34; ++i)
	{
		struct sigaction action;
		action.sa_handler = sighandler;
		ssigfillset(&action.sa_mask);
		action.sa_flags = 0;

  		int r = sigaction (i, &action, NULL);
  		if(r < 0) {
  			perror("Erreur sigaction");
  		}
	}

	errno = 0;

	while(1) {
		swrite(1, ".\n", 2*sizeof(char));
		sleep(1);
		if(errno != 0 && errno!=EINTR) {
			perror("erreur autre que interuption par un signal");
		}
	}
}