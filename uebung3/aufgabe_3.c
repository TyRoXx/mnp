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
			if (*j > *(j + 1))
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
	{
		int *i = data, *end = (data + data_size);
		for (; i != end; ++i)
		{
			*i = rand() % 100;
		}
	}
	
	print_ints(data, data + data_size);
	puts("\n");

	bubble_sort(data, data + data_size);

	print_ints(data, data + data_size);
	return 0;
}
