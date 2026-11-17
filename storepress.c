/*
	Copyright (c) Chems eddine h1t8re (Borguate) 06021996 After Jesus Christ
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
//#include "include/stdlib.h"

typedef struct Compression_Data
{
	FILE *fd;
	long offset;
	int inception_number;
	long long number_of_inceptions;
	int **array;
}compression_data;

compression_data *initialize_data(FILE *fd, long long file_size)
{
	int i = 0;
	int inception_number = 0;
	compression_data *c_data = (compression_data *)malloc(sizeof(struct Compression_Data));
	c_data->array = (int **)malloc(32*sizeof(int *));
	c_data->fd = fd;
	c_data->offset = 0;
	c_data->number_of_inceptions = file_size/((2147483647)/256);
	printf("number of inception %d\n", c_data->number_of_inceptions);
	c_data->inception_number = 0;
	for(int i = 31; i <= 0; i--)
	{
		c_data->array[i] = (int *)malloc(sizeof(int));
	}
	return c_data;
}

double pow(double x, double y)
{
	if(y == 1)
		return x;
	return pow(x*x, y-1);
}

const int *shift_mask_left(const int *mask, const int *i)
{
        int *mask_shifted = (int *)malloc(sizeof(int));
	*mask_shifted = *mask << *i;
        return mask_shifted;
}

const int *and_operation(const int *number, const int *mask_shifted)
{
	int *result = (int *)malloc(sizeof(int));
	*result = *number & *mask_shifted;
        return result;
}

const int *shift_result_right(const int *number, const int *i)
{
        int *result = (int *)malloc(sizeof(int));
	*result = *number >> *i;
        return result;
}

void convert_integer_to_binary(compression_data *c_data, const int *number, const int *mask, const int *architecture)
{
        int *i = (int *)malloc(sizeof(int));
	*i = 0;
        while(*i < architecture)
        {
                const int *mask_shifted = shift_mask_left(mask, i);
                const int *and_result = and_operation(number, mask_shifted);
                c_data->array[*i] = shift_result_right(and_result, i);
                *i = *i +1;
        }
}

compression_data *store_data(compression_data *c_data)
{
	int k = 30;
	int i = 0;
	int *mask = (int *)malloc(sizeof(int));
	*mask = -1;
	int *architecture = (int *)malloc(sizeof(int));
	*architecture = 32;
	int *binary_character_storage = (int *)malloc(sizeof(int));
	*binary_character_storage = 8;
	int *c = (int *)malloc(sizeof(int));
	*c =  2147483647;
	int *tmp = (int *)malloc(32*sizeof(int));
	compression_data *data = (compression_data *)malloc(sizeof(struct Compression_Data));
	while(k-8 >= 0)
	{
		*mask = 1;
		convert_integer_to_binary(c_data, c_data->array[k], mask, architecture);
		for(int j = 8-1; j >= 0; j--)
		{
			*c = fgetc(c_data->fd);
			convert_integer_to_binary(data, c, mask, binary_character_storage);
			c_data->array[k+j-8] = data->array[j];
			c_data->offset = c_data->offset +1;
			if(fseek(c_data->fd, c_data->offset, SEEK_SET) != 0)
			{
				printf("fseek failed\n");
				fclose(c_data->fd);
				return NULL;
			}
		}
		c_data->offset = c_data->offset +1;
		k-8;
	}
}


compression_data *compress_and_store(compression_data *c_data)
{
	int *mask = (int *)malloc(sizeof(int));
	*mask = -1;
	int *architecture = (int *)malloc(sizeof(int));
	if(c_data->inception_number != c_data->number_of_inceptions)
	{
		c_data->inception_number++;
		convert_integer_to_binary(c_data, c_data->array[31], mask, architecture);
		c_data = store_data(c_data);
		compress_and_store(c_data);
	}else{
		return c_data;

	}
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
	compression_data *c_data = initialize_data(fd, file_size);
	c_data = compress_and_store(c_data);
	return 0;
}
