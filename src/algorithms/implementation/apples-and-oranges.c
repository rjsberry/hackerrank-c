// The contents of this file is free and unencumbered software released into the
// public domain. For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int s, t;
	scanf("%d %d\n", &s, &t);

	int a, b;
	scanf("%d %d\n", &a, &b);

	size_t n, m;
	scanf("%zu %zu\n", &n, &m);

	size_t num_apples = 0, num_oranges = 0;

	for (size_t i = 0; i < n; ++i) {
		int apple;
		scanf("%d", &apple);
		if (s <= a + apple && a + apple <= t)
			++num_apples;
	}

	for (size_t i = 0; i < m; ++i) {
		int orange;
		scanf("%d", &orange);
		if (s <= b + orange && b + orange <= t)
			++num_oranges;
	}

	printf("%zu\n%zu\n", num_apples, num_oranges);

	return EXIT_SUCCESS;
}
