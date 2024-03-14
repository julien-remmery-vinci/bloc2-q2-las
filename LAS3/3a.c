#include <stdio.h>
#include <ctype.h>

#include "utils_v1.h"

#define BUFF_LENGTH 255

int main(int argc, char const *argv[])
{
	printf("Entrer des caracteres\n");
	int fd[2];
	spipe(fd);
	int cid = sfork();
	if (cid > 0) {
		sclose(fd[0]);
		char buff[BUFF_LENGTH] = {0};
		int nread;
		while ((nread = sread(0, buff, BUFF_LENGTH)) > 0 ) {
			nwrite(fd[1], buff, nread);
		}
		sclose(fd[1]);
	} else {
		sclose(fd[1]);
		char buff[BUFF_LENGTH] = {0};
		int nread;
		while ((nread = sread(fd[0], buff, BUFF_LENGTH)) > 0 ) {
			for (int i = 0; i < nread; ++i)
			{
				buff[i] = toupper(buff[i]);
			}
			nwrite(1, buff, nread);
		}
		sclose(fd[0]);
	}
}