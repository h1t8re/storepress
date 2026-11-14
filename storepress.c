/*
	Copyright (c) Chems eddine h1t8re (Borguate) 06021996 After Jesus Christ
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "include/stdlib.h"

typedef struct Compression_Data
{
	FILE *fd;
	long offset;
	int inception_number;
	long long number_of_inceptions;
}compression_data;


int *compress_and_store(int *array, compression_data *c_data)
{
	if(fseek(c_data->fd, c_data->offset, SEEK_SET) != 0)
	{
		printf("fseek failed\n");
		fclose(fd);
		return NULL;
	}
	char buffer[9] = {0};
	fread(buffer, 1, 8, c_data->fd);
	printf("%s\n", buffer);
	c_data->offset = c_data->offset +8;
	compress_and_store(array, c_data);
}

void Compress_And_Store(FILE *fd, long long file_size)
{
	printf("%lld\n", file_size);
	int number_of_inceptions = file_size/((2147483648)/(256));
	int i = 0;
	int inception_number = 0;
	printf("%d\n", number_of_inceptions);
	int *array = (int *)malloc(32*sizeof(int));
	compression_data *c_data = (compression_data *)malloc(struct Compression_Data);
	c_data->fd = fd;
	c_data->offset = 0;
	c_data->number_of_inceptions = file_size/((2147483648)/256));
	c_data->inception_number = 0;
	compress_and_store(array, c_data);
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./storepress [file_name]\n");
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
	struct stat st;
	long long file_size = 0;
	if(stat(filename, &st) == 0)
	{
		file_size = (long long)st.st_size;
	}else
	{
		printf("Error getting file size");
		return 2;
	}
	Compress_And_Store(fd, file_size);
	return 0;
}
