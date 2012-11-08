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

static void bubble_sort_int(int *feld, size_t size)
{
	size_t outer;
	for (outer = 1; outer < size; outer++)
	{
		size_t inner;
		for (inner = 0; inner < size-1; inner++)
		{
			if (feld[inner] > feld[inner+1])
			{
				swap_int(feld + inner, feld + inner + 1);
			}
		}
	}
}

static void generate_int(int *dest, size_t size, int (*generator)())
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		dest[i] = generator();
	}
}

static int random_100(void)
{
	return rand() % 100;
}

static void for_each_int(int const *source, size_t size, void (*handler)(int))
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		handler(source[i]);
	}
}

static void print_int_line(int value)
{
	printf("%d\n", value);
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

typedef void (*int_sorter)(int *, size_t);

static int_sorter const sort_functions[] =
{
	bubble_sort_int,
};

static void copy_int_array(int *dest, int const *source, size_t size)
{
	memmove(dest, source, (size * sizeof(*dest)));
}

static int has_same_elements(int const *first, int *destructive_second, size_t size)
{
	size_t i;
	
	for (i = 0; i < size; ++i)
	{
		int const element = first[i];
		int *pos = 0;
		size_t j;
		for (j = i; j < size; ++j)
		{
			if (element == destructive_second[j])
			{
				pos = (destructive_second + j);
				break;
			}
		}
		if (!pos)
		{
			fprintf(stderr, "Element is missing\n");
			return 0;
		}
		swap_int(destructive_second + i, pos);
	}
	
	return 1;
}

static int test_sort_functions(int const *data, size_t size)
{
	size_t const sort_function_count = (sizeof(sort_functions) / sizeof(sort_functions[0]));
	size_t i;
	int * const working_copy = malloc(sizeof(*working_copy) * size);
	if (!working_copy)
	{
		return 0;
	}
	
	for (i = 0; i < sort_function_count; ++i)
	{
		int_sorter const sort = sort_functions[i];
		copy_int_array(working_copy, data, size);
		
		sort(working_copy, size);
		assert(is_sorted(working_copy, size));
	
		printf("\nReihung *nach* der Sortierung:\n");
		for_each_int(working_copy, size, print_int_line);
		
		if (!has_same_elements(data, working_copy, size))
		{
			free(working_copy);
			return 0;
		}
		
		assert(!memcmp(working_copy, data, (size * sizeof(*data))));
	}
	
	free(working_copy);
	return 1;
}

int main(void)
{
	size_t const numbers_size = 10;
	int * const numbers = malloc(sizeof(*numbers) * numbers_size);
	if (!numbers)
	{
		return 1;
	}
	
	srand(1337);
	generate_int(numbers, numbers_size, random_100);

	printf("Reihung *vor* der Sortierung:\n");
	for_each_int(numbers, numbers_size, print_int_line);

	if (!test_sort_functions(numbers, numbers_size))
	{
		free(numbers);
		return 1;
	}
	
	free(numbers);
	return 0;
}