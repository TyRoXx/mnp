#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <time.h>
#include <string.h>

static void swap_int(int *first, int *second)
{
	int const temp = *first;
	*first = *second;
	*second = temp;
}


/*Quicksort*/
static int *min_int_value(int *first, int *second)
{
	return (*first < *second) ? first : second;
}

static int *max_int_value(int *first, int *second)
{
	return (*first > *second) ? first : second;
}

static int *choose_pivot(int *begin, int *end)
{
	int * const first = begin;
	int * const middle = begin + ((end - begin) / 2);
	int * const last = end - 1;
	int * const median =
		max_int_value(
			max_int_value(
				min_int_value(first, middle),
				min_int_value(first, last)
				),
			min_int_value(middle, last)
			);
	return median;
}

static void quick_sort_int(int *begin, int *end)
{
	int *pivot;
	int *i;
	int *right;
	
	if ((end - begin) <= 1)
	{
		return;
	}
	
	pivot = choose_pivot(begin, end);
	right = (end - 1);
	swap_int(right, pivot);
	pivot = right;
	
	for (i = begin; i < right; )
	{
		if (*i > *pivot)
		{
			--right;
			swap_int(i, right);
		}
		else
		{
			++i;
		}
	}
	
	swap_int(pivot, right);
	
	quick_sort_int(begin, right);
	quick_sort_int(right, end);
}


/*Bubble Sort*/
static void bubble_sort_int(int *begin, int *end)
{
	int *i;
	for (i = begin + 1; i < end; ++i)
	{
		int *j;
		for (j = begin; j < (end - 1); ++j)
		{
			if (j[0] > j[1])
			{
				swap_int(j, j + 1);
			}
		}
	}
}


/* C style sort*/
static int int_comparator(void const *left, void const *right)
{
	int const * const left_int = left;
	int const * const right_int = right;
	return (*left_int - *right_int);
}

static void c_lib_sort(int *begin, int *end)
{
	qsort(begin, (end - begin), sizeof(*begin), int_comparator);
}


/*list of tested sort functions*/
typedef void (*int_sorter)(int *, int *);

typedef struct sort_entry_t
{
	int_sorter sort;
	char const *name;
}
sort_entry_t;

static sort_entry_t const sort_functions[] =
{
	{bubble_sort_int, "Bubble Sort"},
	{quick_sort_int, "Quick Sort"},
	{c_lib_sort, "C standard qsort"},
};


static void generate_int(int *dest, size_t size, int (*generator)())
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		dest[i] = generator();
	}
}

static void for_each_int(int const *source, size_t size, void (*handler)(int))
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		handler(source[i]);
	}
}

static int is_sorted(int const *source, size_t size)
{
	size_t i;
	for (i = 1; i < size; ++i)
	{
		if (source[i] < source[i - 1])
		{
			return 0;
		}
	}
	return 1;
}

static void copy_int_array(int *dest, int const *source, size_t size)
{
	memmove(dest, source, (size * sizeof(*dest)));
}

static int reorder_int_array(int const *model, int *reordered, size_t size)
{
	size_t i;
	
	for (i = 0; i < size; ++i)
	{
		int const element = model[i];
		int *pos = 0;
		size_t j;
		for (j = i; j < size; ++j)
		{
			if (element == reordered[j])
			{
				pos = (reordered + j);
				break;
			}
		}
		if (!pos)
		{
			fprintf(stderr, "Element is missing\n");
			return 0;
		}
		swap_int(reordered + i, pos);
	}
	
	return 1;
}

static void print_int_line(int value)
{
	fprintf(stderr, "%d\n", value);
}

static int test_sort_functions(int const *data, size_t size)
{
	int success = 1;
	
	size_t const sort_function_count = (sizeof(sort_functions) / sizeof(sort_functions[0]));
	size_t i;
	int * const working_copy = malloc(sizeof(*working_copy) * size);
	if (!working_copy)
	{
		success = 0;
		goto finish;
	}
	
	for (i = 0; i < sort_function_count; ++i)
	{
		sort_entry_t const sort_entry = sort_functions[i];
		copy_int_array(working_copy, data, size);
		
		sort_entry.sort(working_copy, working_copy + size);
	
		fprintf(stderr, "\n%u: Reihenfolge nach %s:\n", (unsigned)i, sort_entry.name);
		for_each_int(working_copy, size, print_int_line);
		
		assert(is_sorted(working_copy, size));
		
		if (!reorder_int_array(data, working_copy, size))
		{
			success = 0;
			goto finish;
		}
		
		assert(!memcmp(working_copy, data, (size * sizeof(*data))));
	}
	
finish:
	free(working_copy);
	return success;
}

static int random_100(void)
{
	return rand() % 100;
}

int main(void)
{
	int result = 0;
	
	size_t const numbers_size = 10;
	int * const numbers = malloc(sizeof(*numbers) * numbers_size);
	if (!numbers)
	{
		result = 1;
		goto finish;
	}
	
	srand(1337);
	generate_int(numbers, numbers_size, random_100);

	fprintf(stderr, "Reihung vor der Sortierung:\n");
	for_each_int(numbers, numbers_size, print_int_line);

	if (!test_sort_functions(numbers, numbers_size))
	{
		result = 1;
		goto finish;
	}
	
finish:
	free(numbers);
	return result;
}
