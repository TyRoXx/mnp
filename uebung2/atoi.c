#include <stdio.h>

int svs_atoi(const char str[]) {
	...
}

int main() {
	if(svs_atoi("12345") != 12345) {
		printf("%s ist nicht %d\n", "12345", svs_atoi("12345"));
	}

	if(svs_atoi("-987") != -987) {
		printf("%s ist nicht %d\n", "-987", svs_atoi("-987"));
	}

	if(svs_atoi("219540062") != 219540062) {
		printf("%s ist nicht %d\n", "219540062", svs_atoi("219540062"));
	}
	
	return 0;
}
