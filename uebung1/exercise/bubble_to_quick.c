/*	Kompilieren, Linken: gcc -o uebung01 uebung01.c */
/*	Ausfuehren:          ./uebung01                 */
#include <stdio.h>
#include <stdlib.h>
#define MAX 5

void bubble_sort_numbers(int feld[]);
int add_numbers(int feld[], int max);

int main() {
	int loop1,
		randwert,
		numbers[MAX];

	for (loop1=0; loop1<MAX; loop1++) {
		randwert = random() % 100;
		numbers[loop1] = randwert;
	}

	printf("Reihung *vor* der Sortierung:\n");
	for (loop1=0; loop1<MAX; loop1++) {
		printf("%d\n", numbers[loop1]);
	}

	bubble_sort_numbers(numbers);

	printf("\nReihung *nach* der Sortierung:\n");
	for (loop1=0; loop1<MAX; loop1++) {
		printf("%d\n", numbers[loop1]);
	}

	printf("\nSumme: %d\n",add_numbers(numbers,MAX));
	return 0;
}

void bubble_sort_numbers(int feld[]) {
	int outer,
		inner,
		buf;
	for (outer=1; outer<MAX; outer++) {
		for (inner=0; inner<MAX-1; inner++) {
			if (feld[inner] > feld[inner+1]) {
				buf = feld[inner];
				feld[inner] = feld[inner+1];
				feld[inner+1] = buf;
			}
		}
	}
}

int add_numbers(int feld[], int max) {
	int loop1,
		retval = 0;
	for (loop1=0; loop1<max; loop1++) {
		retval += feld[loop1];
	}
	return retval;
}

