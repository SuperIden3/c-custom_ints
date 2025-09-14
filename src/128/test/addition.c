#define INT128_T_IMPLEMENTATION
#include "int128_t.h"

#include <stdio.h>
#include <inttypes.h>

int main(void) {
	int128_t *a = NULL;

	if (int128_new(&a, 1, 1) != INT128_T_SUCCESS) {
		perror("Couldn't allocate int128_t");
		return 1;
	}

	printf("%p: %" PRIu64 " %" PRIu64 "\n", (void*)a, a->hi, a->lo);
	int128_free(&a);

	return 0;
}

