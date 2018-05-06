// The contents of this file is free and unencumbered software released into the
// public domain. For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdlib.h>

struct StackNode {
	int data;
	struct StackNode *next;
};

void destroy_stack(struct StackNode **head)
{
	struct StackNode *tmp;
	while (*head) {
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

void push_stack(struct StackNode **head, int data)
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

int pop_stack(struct StackNode **head)
{
	if (!(*head)->next) {
		int data = (*head)->data;
		destroy_stack(head);
		return data;
	}

	int data = (*head)->data;
	*head = (*head)->next;
	return data;
}

struct MaxStack {
	struct StackNode *main_stack;
	struct StackNode *max_stack;
	struct StackNode *stack_cache;
};

enum InternalStack { MAIN_STACK, MAX_STACK };

struct MaxStack *create_max_stack(void)
{
	struct MaxStack *s = (struct MaxStack *)malloc(sizeof(struct MaxStack));
	s->main_stack = NULL;
	s->max_stack = NULL;
	s->stack_cache = NULL;
	return s;
}

void destroy_max_stack(struct MaxStack **s)
{
	destroy_stack(&(*s)->main_stack);
	destroy_stack(&(*s)->max_stack);
	destroy_stack(&(*s)->stack_cache);
	free(*s);
	*s = NULL;
}

void push(struct MaxStack *s, int data)
{
	if (!s->max_stack || data >= s->max_stack->data) {
		push_stack(&s->max_stack, data);
		push_stack(&s->stack_cache, (int)MAX_STACK);
	}
	else {
		push_stack(&s->main_stack, data);
		push_stack(&s->stack_cache, (int)MAIN_STACK);
	}
}

void pop(struct MaxStack *s)
{
	enum InternalStack which = (enum InternalStack)pop_stack(&s->stack_cache);
	switch (which) {
	case MAIN_STACK:
		pop_stack(&s->main_stack);
		break;
	case MAX_STACK:
		pop_stack(&s->max_stack);
		break;
	}
}

void print_max(struct MaxStack *s)
{
	printf("%d\n", s->max_stack->data);
}

int main(void)
{
	size_t n;
	scanf("%lu", &n);

	struct MaxStack *max_stack = create_max_stack();

	for (size_t i = 0; i < n; ++i) {
		int type, x;
		scanf("%d", &type);

		switch (type) {
		case 1:
			scanf("%d", &x);
			push(max_stack, x);
			break;
		case 2:
			pop(max_stack);
			break;
		case 3:
			print_max(max_stack);
			break;
		default:
			printf("Bad query type: '%d'\n", type);
			destroy_max_stack(&max_stack);
			return EXIT_FAILURE;
		}
	}

	destroy_max_stack(&max_stack);
	return EXIT_SUCCESS;
}
