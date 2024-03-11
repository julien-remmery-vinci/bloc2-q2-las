#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "utils_v1.h"

#define MAX_LENGTH 20
#define BUFF_LENGTH 255

int main(int argc, char const *argv[])
{
	char fname[MAX_LENGTH] = {0};
	sread(0, fname, MAX_LENGTH*sizeof(char));
	int fd = sopen(fname, O_WRONLY | O_TRUNC | O_CREAT, 0700);

	int cid = sfork();
	if(cid == 0) {
		char* tab[] = {"ls", "-l", fname, NULL};
		execv("/bin/ls", tab);
	} else {
		char* str = "#!/bin/bash\n";
		swrite(fd, str, strlen(str)*sizeof(char));
		char buff[BUFF_LENGTH] = {0};
		while(sread(0, &buff, BUFF_LENGTH) > 0) {
			swrite(fd, buff, strlen(buff)*sizeof(char));
		}
		swaitpid(cid, 0, 0);
		cid = sfork();
		if(cid == 0) {
			char* tab[] = {"cat", fname, NULL};
			execv("/bin/cat", tab);
		}
	}
	swaitpid(cid, 0, 0);
	sclose(fd);
}