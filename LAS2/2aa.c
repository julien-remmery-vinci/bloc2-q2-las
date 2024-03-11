#include <stdio.h>

#include "utils_v1.h"

int main(int argc, char const *argv[])
{
	int a = 5;
	int pid = sfork();
	if(pid != 0){
		printf("pid: %i\n", pid);
		int b = a * 5;
		printf("a: %d\nb: %d\n", a, b);
	}
	else{
		int b = a * 2;
		printf("a: %d\nb: %d\n", a, b);
	}
}