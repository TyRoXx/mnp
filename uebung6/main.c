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

static int has_friend_in_range(uint candidate, uint min, uint max)
{
	uint const candidate_sum = sum_of_dividers(candidate);
	return (candidate_sum >= min) &&
			(candidate_sum <= max) &&
			(candidate_sum != candidate) &&
			(candidate == sum_of_dividers(candidate_sum));
}

static uint sum_of_friends(uint min, uint max)
{
	uint sum = 0;
	uint i;
	for (i = min; i <= max; ++i)
	{
		if (has_friend_in_range(i, min, max))
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
	assert(test_friends(18416, 17296));
	assert(has_friend_in_range(220, 284, 284));
	assert(has_friend_in_range(284, 220, 220));
	assert(!has_friend_in_range(220, 284 + 1, 284 + 1));
	assert(!has_friend_in_range(284, 220 + 1, 220 + 1));

	printf("%u\n", sum_of_friends(0, 10000));
	return 0;
}
