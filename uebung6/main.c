#include <stdio.h>
#include <assert.h>

typedef unsigned uint;

static uint sum_of_dividers(uint dividend)
{
	uint sum = 1;
	uint i;
	uint const n = (dividend / 2);
	for (i = 2; i <= n; ++i)
	{
		if (dividend % i == 0)
		{
			sum += i;
		}
	}
	return sum;
}

static int has_friend(uint candidate)
{
	uint const candidate_sum = sum_of_dividers(candidate);
	return (candidate_sum != candidate) &&
			(candidate == sum_of_dividers(candidate_sum));
}

static uint sum_of_friends(uint min, uint max)
{
	uint sum = 0;
	uint i;
	for (i = min; i <= max; ++i)
	{
		if (has_friend(i))
		{
			sum += i;
		}
	}
	return sum;
}

static int test_friends(uint first, uint second)
{
	return sum_of_dividers(first) == second &&
			sum_of_dividers(second) == first;
}

int main(void)
{
	assert(test_friends(220, 284));
	assert(test_friends(1184, 1210));
	assert(test_friends(17296, 18416));
	assert(has_friend(220));
	assert(has_friend(284));
	assert(has_friend(1184));
	assert(has_friend(1210));
	assert(has_friend(17296));
	assert(has_friend(18416));
	assert(!has_friend(0));
	assert(!has_friend(1));
	assert(!has_friend(2));
	assert(!has_friend(220 + 1));
	assert(!has_friend(284 + 1));

	printf("%u\n", sum_of_friends(0, 10000));
	return 0;
}
