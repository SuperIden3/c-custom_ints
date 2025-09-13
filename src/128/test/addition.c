#define INT128_T_IMPLEMENTATION
#include "int128_t.h"

#include <stdio.h>

int main(void) {
	int128_t *a = NULL;
	char *repr = NULL;

	if (int128_new(&a, 1, 1) != INT128_T_SUCCESS) {
		perror("Couldn't allocate int128_t");
		return 1;
	}

	if (int128_tostr(*a, &repr) != INT128_T_SUCCESS) {
		perror("Cannot represent int128_t as a string");
		int128_free(&a);
		return 2;
	}

	printf("%p: %s\n", (void*)a, repr);

	free(repr);
	int128_free(&a);

	return 0;
}

