#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "utils_v1.h"

#define FILE_PATH "/bin/"

void runLs(void* arg0, void* arg1) {
	int* fd = arg0;
	int ret = dup2(fd[1], 1);
	
	sclose(fd[0]);
	sclose(fd[1]);
	
	checkNeg(ret, "erreur dup");
	execlp(arg1, arg1, NULL);
}

void runGrep(void* arg0, void* arg1) {
	int* fd = arg0;
	char** cmd = arg1;
	int ret = dup2(fd[0], 0);
		
	sclose(fd[0]);
	sclose(fd[1]);
	
	checkNeg(ret, "erreur dup");
	execlp(cmd[0], cmd[0], cmd[1], NULL);
}

int main(int argc, char *argv[])
{
	int fd[2];
	spipe(fd);

	int cid1 = fork_and_run2(runLs, fd, argv[1]);
	int cid2 = fork_and_run2(runGrep, fd, &argv[2]);

	sclose(fd[0]);
	sclose(fd[1]);

	swaitpid(cid1, 0, 0);
	swaitpid(cid2, 0, 0);
}
