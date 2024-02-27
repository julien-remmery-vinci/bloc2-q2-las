#include <stdio.h>

int main(int argc, char const *argv[])
{
	FILE* f = fopen("compfwrite", "wb");
	for (int i = 0; i < 10000000; ++i)
	{
		fwrite(&i, 1, sizeof(int), f);
	}
	fclose(f);
}