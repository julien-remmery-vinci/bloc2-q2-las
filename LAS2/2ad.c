#include <stdio.h>

#include "utils_v1.h"

int main(int argc, char const *argv[])
{
	printf("trois.. deux.. un..");
	int pid = sfork();
	if(pid == 0){
		printf("partez !");
	}
}