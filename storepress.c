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
	c_data->offset = c_data->offset +1;
	if(fseek(c_data->fd, c_data->offset, SEEK_SET) != 0)
	{
		printf("fseek failed\n");
		fclose(c_data->fd);
		return NULL;
	}
	int c = fgetc(c_data->fd);
	convert_integer_to_binary(array, c, -1, 32);
	for(int i = 31; i >= 0; i--)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	if(c_data->inception_number == c_data->number_of_inceptions)
	{
		return array;
	}
}

int *Compress_And_Store(FILE *fd, long long file_size)
{
	compression_data *c_data = initialize_data_structure(fd, file_size);
	int *array = (int *)malloc(32*sizeof(int));
	long long *c = (int *)malloc(sizeof(long long))
	*c =  2147483647;
	convert_integer_to_binary(array, *c, -1, 32);
	int *array = compress_and_store(array, c_data);
}

compression_data *initialize_data_structure(FILE *fd, long long file_size)
{
	int i = 0;
	int inception_number = 0;
	int *array = (int *)malloc(32*sizeof(int));
	compression_data *c_data = (compression_data *)malloc(sizeof(struct Compression_Data));
	c_data->fd = fd;
	c_data->offset = 0;
	c_data->number_of_inceptions = file_size/((2147483647)/256);
	c_data->inception_number = 0;
	return c_data;
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
