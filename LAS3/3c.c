#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>                                                                                
#include <sys/stat.h>                                                                                 
#include <fcntl.h>

#include "utils_v1.h"

#define GENERATOR_FILE_NAME "createInscriptionRequests.c"
#define INPUT_FILE_NAME "DemandesInscriptions.bin"
#define BUFF_LENGTH 1024

void generateFile() {
	sexecl("/bin/gcc", "gcc", GENERATOR_FILE_NAME, NULL);
}

void executeFile() {
	sexecl("./a.out", "./a.out", NULL);
}

void removeFile() {
	sexecl("/bin/rm", "rm", "a.out", NULL);
}

int main(int argc, char const *argv[])
{
	int cid1 = fork_and_run0(generateFile);
	swaitpid(cid1, 0, 0);
	int cid2 = fork_and_run0(executeFile);
	swaitpid(cid2, 0, 0);
	int cid3 = fork_and_run0(removeFile);
	swaitpid(cid3, 0, 0);
}