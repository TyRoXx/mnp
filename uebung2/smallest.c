#include <stdio.h>
#include <assert.h>

typedef unsigned integer;

static int is_evenly_divisible(
	integer dividend,
	integer min_divisor,
	integer max_divisor
	)
{
	integer div;
	
	for (div = max_divisor + 1; div-- > min_divisor; )
	{
		if (dividend % div)
		{
			return 0;
		}
	}
	
	return 1;
}

static integer find_smallest_divisible(
	integer min_divisor,
	integer max_divisor
	)
{
	integer i;
	
	assert(min_divisor > 0);
	assert(max_divisor > 0);
	assert(min_divisor <= max_divisor);
	
	printf("Divisor range %u..%u ", min_divisor, max_divisor);
	
	min_divisor = (max_divisor / 2) + 1;
	
	if (min_divisor == 1 &&
		max_divisor > 1)
	{
		min_divisor = 2;
	}
	
	printf("is equivalent to %u..%u\n", min_divisor, max_divisor);
	
	for (i = max_divisor; !is_evenly_divisible(i, min_divisor, max_divisor); i += max_divisor)
	{
	}
	
	return i;
}

int main(void)
{
	assert(find_smallest_divisible(1, 10) == 2520);
	assert(find_smallest_divisible(1, 1) == 1);
	assert(find_smallest_divisible(1, 2) == 2);
	assert(find_smallest_divisible(1, 3) == 6);
	
	printf("Result 1..20: %u\n", find_smallest_divisible(1, 20));
	return 0;
}
