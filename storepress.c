#include <stdio.h>
#include <stdlib.h>
#include "include/stdlib.h"

void Compress_And_Store(FILE *fd)
{
	
}
	
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./storepress [file_name]");
		return 1;
	}
	char *filename = argv[1];
	printf("%s\n", filename);
	FILE *fd = fopen(filename, "r");
	if(fd == NULL)
	{
		printf("Error opening the file\n");
		return 2;
	}
	
	Compress_And_Store(fd);
	return 0;
}
