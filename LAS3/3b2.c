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
	sexecl(arg1, arg1, NULL);
}

void runGrep(void* arg0, void* arg1, void* arg2) {
	int* fd = arg0;
	int ret = dup2(fd[0], 0);
		
	sclose(fd[0]);
	sclose(fd[1]);
	
	checkNeg(ret, "erreur dup");
	sexecl(arg1, arg1, arg2, NULL);
}

int main(int argc, char *argv[])
{
	int fd[2];
	spipe(fd);

	int size1 = strlen(argv[1])+strlen(FILE_PATH);
	char* cmd1 = malloc(size1*sizeof(char));
	sprintf(cmd1, "%s%s", FILE_PATH, argv[1]);

	int size2 = strlen(argv[2])+strlen(FILE_PATH);
	char* cmd2 = malloc(size2*sizeof(char));
	sprintf(cmd2, "%s%s", FILE_PATH, argv[2]);

	int cid1 = fork_and_run2(runLs, fd, cmd1);
	int cid2 = fork_and_run3(runGrep, fd, cmd2, argv[3]);

	sclose(fd[0]);
	sclose(fd[1]);

	swaitpid(cid1, 0, 0);
	swaitpid(cid2, 0, 0);

	free(cmd1);
	free(cmd2);
}