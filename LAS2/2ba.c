#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils_v1.h"

int main(int argc, char const *argv[])
{
	int cid = sfork();
	if(cid != 0) {
		int status;
		swaitpid(cid, &status, 0);
		if (WIFEXITED(status)) {
	        int exit_status = WEXITSTATUS(status);        
	        printf("Exit status of the child: %d\n", exit_status);
	    }
		printf("1 2 3\n");
	} else {
		printf("4 5 6\n");
		exit(0);
	}
}