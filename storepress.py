import sys
import argparse


def convert_integer_to_binary(character, mask, architecture):
	if not isinstance(character, int):
		number = ord(character)
	else:
		number = character
	mask_shifted = 0
	and_operation = 0
	array = []
	for i in range(0, architecture):
		mask_shifted = mask << i
		and_operation = number & mask_shifted
		array.append(and_operation >> i)
	return array[::-1]


def compress_data(file_descriptor, storage_number, array=[]):
	if(len(array) != 0):
		array = convert_integer_to_binary(array[31], -1, 32)
	else:
		array = convert_integer_to_binary(storage_number, -1, 32)
	data = ""
	storage_array = []
	character_array = []
	k = 0
	i = 0
	j = 0
	for x_storage in array[:-1]:
		storage_array = convert_integer_to_binary(x_storage-1, 1, 32)
		storage_array = storage_array[::-1]
		for character in file_descriptor.read(1):
			if(character == ""):
				return array[31]
			j += 1
			character_array = convert_integer_to_binary(character, 1, 8)
			character_array = character_array[::-1]
			while(i < 8):
				storage_array[(k*8)+i] = character_array[i]
				i += 1
			k = k +1
			i = 0
			if(j == 7):
				break
			if(k == 3):
				k = 0
		print(storage_array)
	return array
def main():
	"""
	parser = argparse.ArgumentParser(description="Compressing big data in 32 bits")
	parser.add_argument("-c", "--compress", help="Compressing file")
	parser.add_argument("-d", "--decompress", help="Decompressing file")
	args = parser.parse_args()
	"""
	if len(sys.argv) != 3:
		print("Usage: python3 storepress.py [--compress]|[--deconpress] [file_name]")
		exit(1)
	file_name = sys.argv[2]
	storage_number = (2**31)-1
	array = convert_integer_to_binary(storage_number, -1, 32)
	with open(file_name, "r", encoding="utf-8") as file_descriptor:
		array = compress_data(file_descriptor, storage_number, array)
	with open("compressed_data.glyph", "w", encoding='utf-8') as file_descriptor:
		print(array)
		file_descriptor.write(f"{array[31]}")

if __name__ == "__main__":
	main()
