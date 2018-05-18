// The contents of this file is free and unencumbered software released into the
// public domain. For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int main(void)
{
	size_t n;
	scanf("%zu", &n);

	int *array = (int *)malloc(n * sizeof(int));
	if (!array)
		return EXIT_FAILURE;

	for (size_t i = 0; i < n; ++i)
		scanf("%d", &array[i]);

	qsort(array, n, sizeof(int), cmp);

	int *array_d = (int *)malloc(n * sizeof(int));
	if (!array_d) {
		free(array);
		return EXIT_FAILURE;
	}

	for (size_t i = 0; i < n; ++i)
		array_d[i] = abs(array[i] - array[(i + 1) % n]);

	qsort(array_d, n, sizeof(int), cmp);
	printf("%d\n", array_d[0]);

	free(array);
	free(array_d);
	return EXIT_SUCCESS;
}
