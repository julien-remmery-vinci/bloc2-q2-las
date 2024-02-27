#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils_v1.h"

int main(int argc, char const *argv[])
{
	int fd = open("compwrite.bin", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	checkNeg(fd, "Error opening file");
	for (int i = 0; i < 10000000; ++i)
	{
		int nb = write(fd, &i, sizeof(int));
		checkCond(nb == -1, "Error writing file");
	}
	int res = close(fd);
    checkNeg(res,"Error closing fd");
}