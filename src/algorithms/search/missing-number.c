#include <stdio.h>
#include <stdlib.h>

#define MAX_DIFF 100

void scan_arr_and_loc_min(unsigned int *array, size_t n, unsigned int* min)
{
	scanf("%u", min);
	array[0] = *min;

	for (size_t i = 1; i < n; ++i) {
		unsigned int a;
		scanf("%u", &a);
		array[i] = a;
		if (a < *min)
			*min = a;
	}
}

int main(void)
{
	size_t n;
	scanf("%lu", &n);
	unsigned int *arr = (unsigned int *)malloc(n * sizeof(unsigned int));
	unsigned int a_min;
	scan_arr_and_loc_min(arr, n, &a_min);

	size_t m;
	scanf("%lu", &m);
	unsigned int *brr = (unsigned int *)malloc(m * sizeof(unsigned int));
	unsigned int b_min;
	scan_arr_and_loc_min(brr, m, &b_min);

	unsigned int hash_map[MAX_DIFF] = { 0 };
	unsigned int norm = a_min < b_min ? a_min : b_min;

	for (size_t i = 0; i < n; ++i)
		++hash_map[arr[i] - norm];

	for (size_t i = 0; i < m; ++i)
		--hash_map[brr[i] - norm];

	for (size_t i = 0; i < MAX_DIFF; ++i) {
		if (hash_map[i] > 0)
		printf("%lu ", i + norm);
	}

	free(arr);
	arr = NULL;
	free(brr);
	brr = NULL;

	return EXIT_SUCCESS;
}
