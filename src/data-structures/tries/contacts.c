// The contents of this file is free and unencumbered software released into the
// public domain. For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM_CHARS 26

struct TrieNode {
	char data;
	struct TrieNode *children[NUM_CHARS];
	unsigned int occurrences;
};

struct TrieNode *create_node(char data)
{
	struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));

	node->data = data;
	for (size_t i = 0; i < NUM_CHARS; ++i)
		node->children[i] = NULL;
	node->occurrences = 0;

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

void add_string(struct TrieNode *trie[NUM_CHARS], char *string, struct TrieNode *parent)
{
	if (strcmp(string, "\0")) {
		struct TrieNode **node = &trie[(size_t)string[0] - (size_t)'a'];

		if (!*node)
			*node = create_node(string[0]);

		++(*node)->occurrences;

		memmove(string, string + 1, strlen(string));
		add_string((*node)->children, string, *node);
	}
}

unsigned int occurrences_of(struct TrieNode * const trie[NUM_CHARS], char *string)
{
	struct TrieNode * const node = trie[(size_t)string[0] - (size_t)'a'];

	if (!node)
		return 0;

	if (string[1] == '\0')
		return node->occurrences;

	memmove(string, string + 1, strlen(string));
	return occurrences_of(node->children, string);
}

int main(void)
{
	size_t n;
	scanf("%lu", &n);

	struct TrieNode *trie[NUM_CHARS];

	for (size_t i = 0; i < NUM_CHARS; ++i)
		trie[i] = NULL;

	for (size_t i = 0; i < n; ++i) {
		char command[5], string[22];
		scanf("%s %s", command, string);

		if (!strcmp(command, "add")) {
			add_string(trie, string, NULL);
		}
		else if (!strcmp(command, "find")) {
			printf("%u\n", occurrences_of(trie, string));
		}
		else {
			printf("Invalid command\n");
			destroy_nodes(trie);
			return EXIT_FAILURE;
		}
	}

	destroy_nodes(trie);
	return EXIT_SUCCESS;
}
