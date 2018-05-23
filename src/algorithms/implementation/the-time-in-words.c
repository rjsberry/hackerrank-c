// The contents of this file is free and unencumbered software released into the
// public domain. For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdlib.h>

const char *CONV[29] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen", "", "sixteen",
    "seventeen", "eighteen", "nineteen", "twenty", "twenty one", "twenty two",
    "twenty three", "twenty four", "twenty five", "twenty six", "twenty seven",
    "twenty eight", "twenty nine"
};

void print_time_in_words(unsigned int h, unsigned int m)
{
	switch (m) {
	case 0:
		printf("%s o' clock\n", CONV[(h - 1) % 12]);
		break;
	case 15:
		printf("quarter past %s\n", CONV[(h - 1) % 12]);
		break;
	case 30:
		printf("half past %s\n", CONV[(h - 1) % 12]);
		break;
	case 45:
		printf("quarter to %s\n", CONV[h % 12]);
		break;
	default:
		if (m < 30)
			printf("%s %s past %s\n",
			       CONV[m - 1],
			       m == 1 ? "minute" : "minutes",
			       CONV[(h - 1) % 12]);
		else
			printf("%s %s to %s\n",
			       CONV[60 - m - 1],
			       m == 59 ? "minute" : "minutes",
			       CONV[h % 12]);
		break;
	}
}

int main(void)
{
	unsigned int h, m;
	scanf("%u\n%u\n", &h, &m);

	print_time_in_words(h, m);

	return EXIT_SUCCESS;
}
