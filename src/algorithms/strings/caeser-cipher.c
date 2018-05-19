// The contents of this file is free and unencumbered software released into the
// public domain. For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_lowercase_letter(char c)
{
	return c >= 'a' && c <= 'z';
}

bool is_uppercase_letter(char c)
{
	return c >= 'A' && c <= 'Z';
}

void caeser_cipher(char *string, size_t n, int rotations)
{
	for (size_t i = 0; i < n; ++i)
	{
		if (is_lowercase_letter(string[i]) || is_uppercase_letter(string[i]))
		{
			char offset = is_lowercase_letter(string[i]) ? 'a' : 'A';
			string[i] = abs(string[i] - offset + rotations) % 26 + offset;
		}
	}
}

int main(void)
{
	size_t n;
	scanf("%zu", &n);

	char *string = malloc(n * sizeof(char));
	if (!string)
		return EXIT_FAILURE;

	scanf("%s", string);

	int rotations;
	scanf("%d", &rotations);

	caeser_cipher(string, n, rotations);
	printf("%s\n", string);

	free(string);
	return EXIT_SUCCESS;
}
