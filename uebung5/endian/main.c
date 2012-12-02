#include <stdio.h>
#include <stddef.h>
#include <limits.h>

typedef unsigned short uint16;
typedef unsigned int uint32;

void check_integer_types(void)
{
	int check_uint16[sizeof(uint16) == 2];
	int check_uint32[sizeof(uint32) == 4];
	int check_char_bit[CHAR_BIT == 8];
	(void)check_uint16;
	(void)check_uint32;
	(void)check_char_bit;
}

static uint16 conv_endian_16(uint16 value)
{
	return ((value & 0x00ff) << 8) |
			((value & 0xff00) >> 8);
}

static uint32 conv_endian_32(uint32 value)
{
	return ((value & 0x000000ff) << 24) |
			((value & 0x0000ff00) << 8) |
			((value & 0x00ff0000) >> 8) |
			((value & 0xff000000) >> 24);
}

static void print_binary_8(
		FILE *dest,
		unsigned char value)
{
	size_t i;
	for (i = 0; i < 8; ++i, value <<= 1)
	{
		fputc((value & 0x80) ? '1' : '0', dest);
	}
}

static void print_binary_16_be(
		FILE *dest,
		uint16 value)
{
	print_binary_8(dest, (unsigned char)(value >> 8));
	fputc(' ', dest);
	print_binary_8(dest, (unsigned char)value);
}

static void print_binary_range_16_both(
		FILE *dest,
		uint16 min,
		uint16 max)
{
	uint32 i;

	fprintf(dest, "%-19s", "Big Endian");
	fputs("Little Endian\n", dest);

	for (i = min; i <= max; ++i)
	{
		print_binary_16_be(dest, (uint16)i);
		fputs("  ", dest);
		print_binary_16_be(dest, conv_endian_16((uint16)i));
		fputc('\n', dest);
	}
}

static int create_endianness_comparison_file(
		char const *path)
{
	FILE * const file = fopen(path, "w");
	if (!file)
	{
		return 0;
	}
	print_binary_range_16_both(file, 1, 32);
	fclose(file);
	return 1;
}

int main(void)
{
	if (!create_endianness_comparison_file("endian-compare.txt"))
	{
		return 1;
	}
	(void)conv_endian_32;
	return 0;
}

