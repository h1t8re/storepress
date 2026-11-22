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
	compression_data *c_data = (compression_data *)malloc(sizeof(struct Compression_Data));
	c_data->array = (int **)malloc(32*sizeof(int *));
	c_data->fd = fd;
	c_data->offset = 0;
	c_data->number_of_inceptions = file_size/((2147483647)/256);
	c_data->inception_number = 0;
	while(i < 32)
	{
		c_data->array[i] = (int *)malloc(sizeof(int));
		i++;
	}
	return c_data;
}

int strlen(const char *str)
{
        int length = 0;
        while(*(str+(length*sizeof(char))) != '\0')
                length++;
        return length;
}

int strcmp(const char *str0,const char *str1)
{
        if(strlen(str0) != strlen(str1))
                return 1;
	int i = 0;
	while((*(str0+(i*sizeof(char))) == (*(str1+(i*sizeof(char))))) & (*(str0+(i*sizeof(char))) != '\0'))
                i++;
        if(i == strlen(str1))
                        return 0;
        return 1;
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

void convert_integer_to_binary(int **array, const int *number, const int *mask, const int *architecture)
{
        int *i = (int *)malloc(sizeof(int));
	*i = 0;
        while(*i < *architecture)
        {
                const int *mask_shifted = shift_mask_left(mask, i);
                const int *and_result = and_operation(number, mask_shifted);
                array[*i] = shift_result_right(and_result, i);
                *i = *i +1;
        }
}

int convert_binary_to_integer(int **array, int architecture)
{
        int number = 0;
        int i = architecture-1;
        while(i >= 0)
        {
                if(*array[i] == 1)
                        number = number + pow(2, i+1);
                i = i -1;
        }
        return number;
}

compression_data *store_data(compression_data *c_data)
{
	int x = 4;
	int k = 30;
	int i = 8;
	int n = 0;
	int *mask = (int *)malloc(sizeof(int));
	*mask = 1;
	int *architecture = (int *)malloc(sizeof(int));
	*architecture = 32;
	int *char_size = (int *)malloc(sizeof(int));
	*char_size = 8;
	int *c = (int *)malloc(sizeof(int));
	*c =  2147483647;
	compression_data *data = (compression_data *)malloc(sizeof(struct Compression_Data));
	data->array = (int **)malloc(8*sizeof(int *));
	while(n < 32)
	{
		data->array[n] = (int *)malloc(sizeof(int));
		n++;
	}
	while(k > 0)
	{
		convert_integer_to_binary(c_data->array, c_data->array[k], mask, architecture);
		x = k / 8;
		while(x >= 0)
		{
			for(int j = 8-1; j >= 0; j--)
			{
				*c = fgetc(c_data->fd);
				if(*c == EOF)
				{
					return c_data;
				}
				convert_integer_to_binary(data->array, c, mask, char_size);
				c_data->array[(x*8)+j] = data->array[j];
				c_data->offset = c_data->offset +1;
				if(fseek(c_data->fd, c_data->offset, SEEK_SET) != 0)
				{
					fclose(c_data->fd);
					return c_data;
				}
			}
			x = x-1;
		}
		k = k -1;
		x = 4;
	}
	return c_data;
}


compression_data *compress_and_store(compression_data *c_data)
{
	int *mask = (int *)malloc(sizeof(int));
	*mask = -1;
	int *architecture = (int *)malloc(sizeof(int));
	*architecture = 32;
	if(c_data->inception_number != c_data->number_of_inceptions)
	{
		c_data->inception_number++;
		convert_integer_to_binary(c_data->array, c_data->array[31], mask, architecture);
		c_data = store_data(c_data);
		return compress_and_store(c_data);
	}else{
		return c_data;

	}
}

void decompress_data(compression_data *c_data, int *storage_number)
{
	FILE *fd = fopen("data.glyph", "w");
	compression_data *data0 = initialize_data(NULL, 1);
	compression_data *data = initialize_data(NULL, 1);
	int *mask = (int *)malloc(sizeof(int));
	*mask = -1;
	int *architecture = (int *)malloc(sizeof(int));
	*architecture = 32;
	int k = 30;
	int i = 0;
	int x = 4;
	int *number = (int *)malloc(sizeof(int));
	int **array = (int **)malloc(*architecture*sizeof(int *));
	int **array1 = (int **)malloc(8*sizeof(int *));
	int **tmp = (int **)malloc(8*sizeof(int *));
	while(i < 32)
	{
		array[i] = (int *)malloc(sizeof(int));
		i++;
	}
	i = 0;
	while(i < 8)
	{
		array1[i] = (int *)malloc(sizeof(int));
		i++;
	}
	i = 0;
	while(i < 8)
	{
		tmp[i] = (int *)malloc(sizeof(int));
		i++;
	}
	printf("1\n");
	i = 0;
	convert_integer_to_binary(c_data->array, storage_number, mask, architecture);
	*mask = 1;
	*number = 2147483647;
	convert_integer_to_binary(data0->array, number, mask, architecture);
	while(k >= 1)
	{
		*mask = -1;
		convert_integer_to_binary(data->array, c_data->array[k], mask, architecture);
		x = 3;
		while(x >= 0)
		{
			for(int j = 8-1; j >= 0; j++)
			{
				array1[j] = data->array[(x*8)+j];
				printf("%d\n", (8*x)+j);
			}
			/*for(int c = 0; c < 8; c++)
			{
				*tmp[c] = *array1[8-c-1];
			}*/
			*number = convert_binary_to_integer(array1, 8);
			printf("%c", *number);
			fprintf(fd, "%c", *number);
			x = x -1;
		}
		k = k -1;
	}
	decompress_data(c_data, c_data->array[31]);
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: ./storepress [--compress]|[--decompress] [file_name]\n");
		return 1;
	}
	char *filename = argv[2];
	FILE *fd = fopen(filename, "r");
	if(fd == NULL)
	{
		printf("Error opening the file\n");
		return 2;
	}
	printf("%s\n", argv[2]);
	if(strcmp(argv[1], "--compress\0") == 0)
	{
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
		int *mask = (int *)malloc(sizeof(int));
		*mask = -1;
		int *architecture = (int *)malloc(sizeof(int));
		*architecture = 32;
		int *storage = (int *)malloc(sizeof(int));
		*storage = 2147483647;
		convert_integer_to_binary(c_data->array, storage, mask, architecture);
		c_data = compress_and_store(c_data);
		FILE *compressed_data_file = fopen("compressed_data.glyph", "w");
		fprintf(compressed_data_file, "%d", *storage);
	}else if(strcmp(argv[1], "--decompress\0") == 0)
	{
		compression_data *c_data = initialize_data(fd, 1);
		int *storage_number = (int *)malloc(sizeof(int));
		fscanf(fd, "%d", storage_number);
		printf("0\n");
		decompress_data(c_data, storage_number);
		printf("%d\n", *storage_number);
	}
	return 0;
}
