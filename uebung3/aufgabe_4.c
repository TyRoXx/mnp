#include <stdio.h>
#include <assert.h>

typedef size_t integer;

static int is_even(integer n)
{
	return !(n % 2);
}

static size_t collatz_length(integer n)
{
	size_t length = 1;
	
	while (n != 1)
	{
		if (is_even(n))
		{
			n = n / 2;
		}
		else
		{
			n = 3 * n + 1;
		}
		
		++length;
	}
	
	return length;
}

typedef struct sequence_info_t
{
	integer start;
	size_t length;
}
sequence_info_t;

static sequence_info_t find_longest_sequence(integer min, integer max)
{
	sequence_info_t result = {};
	
	for (; min <= max; ++min)
	{
		size_t const length = collatz_length(min);
		if (length > result.length)
		{
			result.length = length;
			result.start = min;
		}
	}
	
	return result;
}

static void print_longest_sequence(integer min, integer max)
{
	sequence_info_t const sequence = find_longest_sequence(min, max);
	printf("%u..%u -> start %u, length %u\n",
		(unsigned)min,
		(unsigned)max,
		(unsigned)sequence.start,
		(unsigned)sequence.length
		);
}

int main(void)
{
	assert(collatz_length(1) == 1);
	assert(collatz_length(2) == 2);
	assert(collatz_length(13) == 10);
	
	print_longest_sequence(1, 1);
	print_longest_sequence(1, 10);
	print_longest_sequence(1, 1000);
	print_longest_sequence(1, 1000000);
	return 0;
}
