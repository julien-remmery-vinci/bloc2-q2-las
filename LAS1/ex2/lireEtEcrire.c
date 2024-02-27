#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "utils_v1.h"

#define MAX_SIZE 80

int main(int argc, char const *argv[])
{
	if(argc < 3) {
		perror("not enough file names provided");
		exit(1);
	}

	int fd1 = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	checkNeg(fd1, "Error opening first file");

	int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	checkNeg(fd2, "Error opening second file");
	
	char bufRd[MAX_SIZE];
	int nbCharRd = read(0, bufRd, MAX_SIZE);
	int nbCharWr;
	while (nbCharRd > 0) {
		if(isalpha(bufRd[0])){
			if(isupper(bufRd[0])){
				nbCharWr = write(fd1, bufRd, nbCharRd);
				checkCond(nbCharWr != nbCharRd,"Error writing file");
			}
			else{
				nbCharWr = write(fd2, bufRd, nbCharRd);
				checkCond(nbCharWr != nbCharRd,"Error writing file");
			}
		}
		nbCharRd = read(0, bufRd, MAX_SIZE);
	}

	checkNeg(nbCharRd,"Error reading stdin");

	/* Closing fd */
	int res = close(fd1);
	checkNeg(res,"Error closing fd");
	res = close(fd2);
	checkNeg(res,"Error closing fd");
}
