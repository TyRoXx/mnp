#include <stdio.h>

static void print_ints(int const *a, size_t n)
{
	size_t i;
	for (i = 0; i < n; ++i)
	{
		printf("%d\n", a[i]);
	}
}

int main(void)
{
	/* Definiere zwei Vektoren der Laenge 10; */
	/* Initialisiere sie mit 1 bzw . 2 */
	
	int v1[10];
	int v2[10];
	size_t i;
	
	for (i = 0; i < 10; ++i)
	{
		v1[i] = 1;
		v2[i] = 2;
	}
	
	print_ints(v1, 10);
	print_ints(v2, 10);
	
	return 0;
}
