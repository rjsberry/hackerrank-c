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

struct Queue {
	struct StackNode *stack1;
	struct StackNode *stack2;
};

struct Queue *create_queue(void)
{
	struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
	q->stack1 = NULL;
	q->stack2 = NULL;
	return q;
}

void destroy_queue(struct Queue **q)
{
	destroy_stack(&(*q)->stack1);
	destroy_stack(&(*q)->stack2);
	free(*q);
	*q = NULL;
}

void update_stacks(struct Queue *q)
{
	if (!q->stack1)
		while (q->stack2)
			push_stack(&q->stack1, pop_stack(&q->stack2));
}

void enqueue(struct Queue *q, int data)
{
	push_stack(&q->stack2, data);
}

void dequeue(struct Queue *q)
{
	update_stacks(q);
	pop_stack(&q->stack1);
}

void print_head(struct Queue *q)
{
	update_stacks(q);
	printf("%d\n", q->stack1->data);
}

int main(void)
{
	size_t q;
	scanf("%lu", &q);

	struct Queue *queue = create_queue();

	for (size_t i = 0; i < q; ++i) {
		int type, x;
		scanf("%d", &type);

		switch (type) {
		case 1:
			scanf("%d", &x);
			enqueue(queue, x);
			break;
		case 2:
			dequeue(queue);
			break;
		case 3:
			print_head(queue);
			break;
		default:
			printf("Bad query type: '%d'\n", type);
			destroy_queue(&queue);
			return EXIT_FAILURE;
		}
	}

	destroy_queue(&queue);
	return EXIT_SUCCESS;
}
