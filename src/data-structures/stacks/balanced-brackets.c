// The contents of this file is free and unencumbered software released into the
// public domain. For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct StackNode {
	char data;
	struct StackNode *next;
};

void destroy(struct StackNode **head)
{
	struct StackNode *tmp;
	while (*head) {
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

void push(struct StackNode **head, int data)
{
	struct StackNode *node = (struct StackNode *)malloc(sizeof(struct StackNode));
	node->data = data;
	node->next = NULL;

	if (!*head) {
		*head = node;
	}
	else {
		node->next = *head;
		*head = node;
	}
}

char pop(struct StackNode **head)
{
	if (!(*head)->next) {
		char data = (*head)->data;
		destroy(head);
		return data;
	}

	char data = (*head)->data;
	*head = (*head)->next;
	return data;
}

bool is_open_bracket(char bracket)
{
	return bracket == '(' || bracket == '[' || bracket == '{';
}

bool is_closed_bracket(char bracket)
{
	return bracket == ')' || bracket == ']' || bracket == '}';
}

bool is_pair(char open, char close)
{
	switch (open) {
	case '(':
		return close == ')';
	case '[':
		return close == ']';
	case '{':
		return close == '}';
	}
	return false;
}

int main(void)
{
	size_t n;
	scanf("%lu", &n);

	for (size_t i = 0; i < n; ++i) {
		char string[1024];
		scanf("%s", string);

		struct StackNode *stack = NULL;
		bool balanced = true;

		for (size_t j = 0; j < strlen(string) && balanced; ++j) {
			char bracket = string[j];

			if (is_open_bracket(bracket))
				push(&stack, bracket);
			else if (is_closed_bracket(bracket) &&
			         !stack ||
			         !is_pair(pop(&stack), bracket))
				balanced = false;
		}

		printf(balanced && !stack ? "YES\n" : "NO\n");
		destroy(&stack);
	}

	return EXIT_SUCCESS;
}
