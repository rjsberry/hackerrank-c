// The contents of this file is free and unencumbered software released into the
// public domain. For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DisjointSetForest {
	size_t *parent;
	int *rank;
	size_t *set_len;
	size_t len;
};

static struct DisjointSetForest *dsf_create(size_t len)
{
	struct DisjointSetForest *dsf = malloc(sizeof(struct DisjointSetForest));
	if (!dsf)
		goto fail;

	dsf->parent = malloc(len * sizeof(size_t));
	if (!dsf->parent)
		goto fail_free_dsf;

	dsf->rank = malloc(len * sizeof(int));
	if (!dsf->rank)
		goto fail_free_parent_free_dsf;

	dsf->set_len = malloc(len * sizeof(size_t));
	if (!dsf->set_len)
		goto fail_free_rank_free_parent_free_dsf;

	for (size_t i = 0; i < len; ++i) {
		dsf->parent[i] = i;
		dsf->rank[i] = 0;
		dsf->set_len[i] = 1;
	}

	dsf->len = len;

	return dsf;

fail_free_rank_free_parent_free_dsf:
	free(dsf->rank);

fail_free_parent_free_dsf:
	free(dsf->parent);

fail_free_dsf:
	free(dsf);

fail:
	return NULL;
}

static void dsf_destroy(struct DisjointSetForest **dsf)
{
	free((*dsf)->parent);
	free((*dsf)->rank);
	free((*dsf)->set_len);

	free(*dsf);
	*dsf = NULL;
}

static size_t dsf_find_root(struct DisjointSetForest *dsf, size_t i)
{
	if (i != dsf->parent[i])
		dsf->parent[i] = dsf_find_root(dsf, dsf->parent[i]);

	return dsf->parent[i];
}

static void dsf_link_parents(struct DisjointSetForest *dsf, size_t i, size_t j)
{
	if (i != j) {
		if (dsf->rank[i] == dsf->rank[j])
			++dsf->rank[j];

		if (dsf->rank[i] > dsf->rank[j]) {
			dsf->parent[j] = i;
			dsf->set_len[i] += dsf->set_len[j];
		}
		else {
			dsf->parent[i] = j;
			dsf->set_len[j] += dsf->set_len[i];
		}
	}
}

static void dsf_make_union(struct DisjointSetForest *dsf, size_t i, size_t j)
{
	dsf_link_parents(dsf, dsf_find_root(dsf, i), dsf_find_root(dsf, j));
}

static size_t dsf_set_size(struct DisjointSetForest *dsf, size_t i)
{
	return dsf->set_len[dsf->parent[dsf_find_root(dsf, i)]];
}

int main(void)
{
	size_t n, q;
	scanf("%zu %zu\n", &n, &q);

	struct DisjointSetForest *dsf = dsf_create(n);
	if (!dsf)
		return EXIT_FAILURE;

	for (size_t i = 0; i < q; ++i) {
		char command;
		size_t i, j;
		scanf("%c", &command);

		switch (command) {
		case 'M':
			scanf("%zu %zu\n", &i, &j);
			dsf_make_union(dsf, i - 1, j - 1);
			break;
		case 'Q':
			scanf("%zu\n", &i);
			printf("%zu\n", dsf_set_size(dsf, i - 1));
			break;
		default:
			printf("Invalid command\n");
			dsf_destroy(&dsf);
			return EXIT_FAILURE;
		}
	}

	dsf_destroy(&dsf);
	return EXIT_SUCCESS;
}
