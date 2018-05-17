// The contents of this file is free and unencumbered software released into the
// public domain. For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM_CHARS 10

struct TrieNode {
	char data;
	struct TrieNode *children[NUM_CHARS];
	unsigned int occurrences;
	bool word_end;
};

struct TrieNode *create_node(char data)
{
	struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));

	node->data = data;
	for (size_t i = 0; i < NUM_CHARS; ++i)
		node->children[i] = NULL;
	node->occurrences = 0;
	node->word_end = false;

	return node;
}

void destroy_nodes(struct TrieNode *trie[NUM_CHARS])
{
	for (size_t i = 0; i < NUM_CHARS; ++i) {
		if (trie[i]) {
			destroy_nodes(trie[i]->children);
			free(trie[i]);
			trie[i] = NULL;
		}
	}
}

void add_string(struct TrieNode *trie[NUM_CHARS], char *string)
{
	if (strcmp(string, "\0")) {
		struct TrieNode **node = &trie[(size_t)string[0] - (size_t)'a'];

		if (!*node)
			*node = create_node(string[0]);

		++(*node)->occurrences;

		if (string[1] == '\0') {
			(*node)->word_end = true;
			return;
		}

		add_string((*node)->children, &string[1]);
	}
}

bool is_prefixed(struct TrieNode * const trie[NUM_CHARS], char *string)
{
	if (strcmp(string, "\0")) {
		struct TrieNode * const node = trie[(size_t)string[0] - (size_t)'a'];

		if (!node)
			return false;

		if (node->occurrences > 1 && node->word_end)
			return true;

		return false || is_prefixed(node->children, &string[1]);
	}

	return false;
}

int main(void)
{
	size_t n;
	scanf("%lu", &n);

	struct TrieNode *trie[NUM_CHARS];

	for (size_t i = 0; i < NUM_CHARS; ++i)
		trie[i] = NULL;

	for (size_t i = 0; i < n; ++i) {
		char string[64];
		scanf("%s", string);

		add_string(trie, string);

		if (is_prefixed(trie, string)) {
			printf("BAD SET\n%s\n", string);
			goto exit_free_trie;
		}
	}

	printf("GOOD SET\n");

exit_free_trie:
	destroy_nodes(trie);
	return EXIT_SUCCESS;
}
