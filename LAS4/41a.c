#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils_v1.h"

int main(int argc, char const *argv[])
{
	int cid = sfork();
	if(cid == 0) {
		while(1) {
			sleep(1);
		}
	}
}