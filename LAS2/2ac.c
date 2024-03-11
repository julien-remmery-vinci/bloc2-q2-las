#include <unistd.h>
#include <string.h>

#include "utils_v1.h"

int main(int argc, char const *argv[])
{
	char* s = "trois.. deux.. un..\n";
	write(1, s, strlen(s));
	int pid = sfork();
	if(pid == 0){
		char* s1 = "partez !\n";
		write(1, s1, strlen(s1));
	}
}