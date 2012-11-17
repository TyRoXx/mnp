#include <stdio.h>
#include <stdlib.h>

static void print_ints(int const *begin, int const *end)
{
	for (; begin != end; ++begin)
	{
		printf("%d\n", *begin);
	}
}

static void swap(int *first, int *second)
{
	*first ^= *second;
	*second ^= *first;
	*first ^= *second;
}

static void bubble_sort(int *begin, int *end)
{
	int *i;
	for (i = begin + 1; i < end; ++i)
	{
		int *j;
		for (j = begin; (j + 1) < end; ++j)
		{
			if (j[0] > j[1])
			{
				swap(j, j + 1);
			}
		}
	}
}

enum
{
	data_size = 10,
};

int main(void)
{
	int data[data_size];
	size_t i;
	for (i = 0; i < data_size; ++i)
	{
		data[i] = rand() % 100;
	}
	
	bubble_sort(data, data + data_size);
	print_ints(data, data + data_size);
	return 0;
}
