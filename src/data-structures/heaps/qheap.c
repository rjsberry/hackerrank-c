// The contents of this file is free and unencumbered software released into the
// public domain. For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdlib.h>

struct Heap {
	int *data;
	size_t len;
};

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

size_t previous_node(size_t i)
{
	return i ? (i - 1)/2 : 0;
}

void sort_up(struct Heap *heap, size_t from)
{
	if (heap->data[from] < heap->data[previous_node(from)]) {
		swap(&heap->data[from], &heap->data[previous_node(from)]);
		sort_up(heap, previous_node(from));
	}
}

void push(struct Heap *heap, int data)
{
	heap->data[heap->len] = data;
	sort_up(heap, heap->len++);
}

size_t index_of(int *array, size_t n, int search)
{
	for (size_t i = 0; i < n; ++i)
		if (array[i] == search)
			return i;
	return n;
}

void sort_down(struct Heap *heap, size_t from)
{
	size_t next_left = 2*from + 1;
	size_t next_right = 2*from + 2;

	if (next_left >= heap->len || next_right >= heap->len)
		return;

	int left = heap->data[next_left];
	int right = heap->data[next_right];

	size_t target = left < right ? next_left : next_right;

	if (heap->data[from] > heap->data[target]) {
		swap(&heap->data[target], &heap->data[from]);
		sort_down(heap, target);
	}
}

void pop(struct Heap *heap, int data)
{
	size_t at = index_of(heap->data, heap->len, data);
	heap->data[at] = heap->data[--heap->len];
	sort_down(heap, at);
}

void print_min(const struct Heap *heap)
{
	printf("%d\n", heap->data[0]);
}

int main(void)
{
	struct Heap heap;
	heap.len = 0;

	size_t q;
	scanf("%lu", &q);

	heap.data = (int *)malloc(q * sizeof(int));

	for (size_t i = 0; i < q; ++i) {     
		int type, x;
		scanf("%d", &type);

		switch (type) {
		case 1:
			scanf("%d", &x);
			push(&heap, x);
			break;
		case 2:
			scanf("%d", &x);
			pop(&heap, x);
			break;
		case 3:
			print_min(&heap);
			break;
		default:
			printf("Bad query type: '%d'\n", type);
			free(heap.data);
			return EXIT_FAILURE;
		}
	}

	free(heap.data);
	return EXIT_SUCCESS;
}
