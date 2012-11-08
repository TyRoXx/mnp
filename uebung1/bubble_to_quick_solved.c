#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <time.h>

static void bubble_sort_numbers(int feld[], size_t size)
{
	size_t outer;
	for (outer=1; outer<size; outer++)
	{
		size_t inner;
		for (inner=0; inner<size-1; inner++)
		{
			if (feld[inner] > feld[inner+1])
			{
				int const buf = feld[inner];
				feld[inner] = feld[inner+1];
				feld[inner+1] = buf;
			}
		}
	}
}

static int add_numbers(int feld[], size_t size)
{
	int sum = 0;
	size_t i;
	for (i = 0; i < size; ++i)
	{
		sum += feld[i];
	}
	return sum;
}

static void generate_int(int *dest, size_t size, int (*generator)())
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		dest[i] = generator();
	}
}

static int random_100()
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

int main() {
	size_t const numbers_size = 10;
	int *numbers = malloc(sizeof(*numbers) * numbers_size);
	if (!numbers)
	{
		return 1;
	}
	
	srand(1337);
	generate_int(numbers, numbers_size, random_100);

	printf("Reihung *vor* der Sortierung:\n");
	for_each_int(numbers, numbers_size, print_int_line);

	bubble_sort_numbers(numbers, numbers_size);
	assert(is_sorted(numbers, numbers_size));
	
	printf("\nReihung *nach* der Sortierung:\n");
	for_each_int(numbers, numbers_size, print_int_line);

	printf("\nSumme: %d\n", add_numbers(numbers, numbers_size));
	return 0;
}