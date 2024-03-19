#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>                                                                                
#include <sys/stat.h>                                                                                 
#include <fcntl.h>

#include "utils_v1.h"

#define GENERATOR_FILE_NAME "createInscriptionRequests.c"
#define GENERATED_FILE_NAME "a.out"
#define INPUT_FILE_NAME "DemandesInscriptions.bin"
#define BUFF_LENGTH 1024

void generateFile() {
	sexecl("/bin/gcc", "gcc", GENERATOR_FILE_NAME, NULL);
}

void executeFile() {
	sexecl("./a.out", GENERATED_FILE_NAME, NULL);
}

void removeFiles() {
	sexecl("/bin/rm", "rm", GENERATED_FILE_NAME, INPUT_FILE_NAME, NULL);
}

int main(int argc, char const *argv[])
{
	int cid1 = fork_and_run0(generateFile);
	swaitpid(cid1, 0, 0);
	int cid2 = fork_and_run0(executeFile);
	swaitpid(cid2, 0, 0);

	int send[2];
	int receive[2];
	spipe(send);
	spipe(receive);

	int nread;
	char buff[BUFF_LENGTH];
	// int pere = 1;
	// int nbSaved = 0;
	// InscriptionRequest ir;
	int fd = sopen(INPUT_FILE_NAME, O_RDONLY, 0);
	while((nread = sread(fd, buff, BUFF_LENGTH)) > 0) {
		// strcpy(ir.name, strtok(buff, " "));
		// strcpy(ir.firstname, strtok(buff, " "));
		// ir.nbYearPastInEducation = atoi(strtok(buff, " "));
		// pere = 0;

		// int cid = sfork();
		// if(cid > 0) {

		// } else {

		// }
		swrite(0, buff, nread);
	}

	int cid3 = fork_and_run0(removeFiles);
	swaitpid(cid3, 0, 0);
}