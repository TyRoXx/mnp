#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include <assert.h>

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

#define DEFINE_CONV_ENDIAN_FUNC(type__, name__) \
type__ name__(type__ value) \
{ \
	type__ result = 0; \
	size_t i; \
	for (i = 0; i < (sizeof(value) / 2); ++i) \
	{ \
		size_t const first_shift = (8 * i); \
		size_t const second_shift = (8 * (sizeof(value) - i - 1)); \
		unsigned char const first = \
				(unsigned char)(value >> first_shift); \
		unsigned char const second = \
				(unsigned char)(value >> second_shift); \
		result |= (type__)(first << second_shift); \
		result |= (type__)(second << first_shift); \
	} \
	return result; \
}

static DEFINE_CONV_ENDIAN_FUNC(uint16, conv_endian_16)
static DEFINE_CONV_ENDIAN_FUNC(uint32, conv_endian_32)
static DEFINE_CONV_ENDIAN_FUNC(unsigned short, conv_endian_short)
static DEFINE_CONV_ENDIAN_FUNC(unsigned int, conv_endian_int)
static DEFINE_CONV_ENDIAN_FUNC(unsigned long, conv_endian_long)

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
		fprintf(stderr, "Could not open file %s\n",
				path);
		return 0;
	}
	print_binary_range_16_both(file, 1, 32);
	fclose(file);
	return 1;
}

#define DEFINE_TEST_CONV_ENDIAN_FUNC(type__, name__, conv__) \
int name__(FILE *error_out) \
{ \
	int success = 1; \
	size_t const max = (type__)0xffff; \
	size_t i; \
	for (i = 0; i <= max; ++i) \
	{ \
		type__ const original = (type__)i; \
		type__ const converted = conv__(original); \
		type__ const back = conv__(converted); \
		if (original != back) \
		{ \
			fprintf(error_out, "%s: Endian conversion failed for %u\n", \
					#name__, (unsigned)i); \
			success = 0; \
		} \
	} \
	return success; \
}

static DEFINE_TEST_CONV_ENDIAN_FUNC(uint16, test_conv_endian_16, conv_endian_16)
static DEFINE_TEST_CONV_ENDIAN_FUNC(unsigned short, test_conv_endian_short, conv_endian_short)
static DEFINE_TEST_CONV_ENDIAN_FUNC(unsigned int, test_conv_endian_int, conv_endian_int)
static DEFINE_TEST_CONV_ENDIAN_FUNC(unsigned long, test_conv_endian_long, conv_endian_long)

int main(void)
{
	assert(conv_endian_32(0x0000aabb) == 0xbbaa0000);
	assert(conv_endian_32(0x00aabbcc) == 0xccbbaa00);
	assert(conv_endian_32(0xaabbccdd) == 0xddccbbaa);
	assert(conv_endian_32(0xffffffff) == 0xffffffff);
	assert(conv_endian_32(0) == 0);
	assert(conv_endian_16(0xaabb) == 0xbbaa);
	assert(conv_endian_16(0xffff) == 0xffff);
	assert(conv_endian_16(0) == 0);

	if (test_conv_endian_16(stderr) &
		test_conv_endian_short(stderr) &
		test_conv_endian_int(stderr) &
		test_conv_endian_long(stderr) &
		create_endianness_comparison_file("endian-compare.txt"))
	{
		fprintf(stderr, "All tests passed\n");
		return 0;
	}
	else
	{
		return 1;
	}
}

