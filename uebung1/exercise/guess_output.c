#include <stdio.h>

int side_effect;

void stat() {
	static int here;
	int tmp;

	printf("%d %d\n", here+=10, tmp);
	side_effect = side_effect + here;
}

int main() {
	printf("%d\n", side_effect);
	stat();
	stat();
	stat();
	printf("%d\n", side_effect);

	return 0;
}
