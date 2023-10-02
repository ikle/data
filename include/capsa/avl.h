/*
 * AVL Tree
 *
 * Copyright (c) 2010-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_AVL_H
#define CAPSA_AVL_H  1

#include <stddef.h>

struct avl {
	struct avl *child[2];
	int h;
};

typedef struct avl *avl_alloc_cb (const void *key);
typedef void avl_free_cb (struct avl *node);
typedef void avl_walk_cb (struct avl *node, void *cookie);
typedef int avl_cmp_cb (const void *key, const struct avl *node);

void   avl_free  (struct avl *root, avl_free_cb *free);
void   avl_walk  (struct avl *root, avl_walk_cb *poke, void *cookie);
size_t avl_count (struct avl *root);

struct avl *avl_find    (struct avl **root, const void *key, avl_cmp_cb *cmp);
struct avl *avl_find_lo (struct avl **root, const void *key, avl_cmp_cb *cmp);
struct avl *avl_find_hi (struct avl **root, const void *key, avl_cmp_cb *cmp);
struct avl *avl_search  (struct avl **root, const void *key, avl_cmp_cb *cmp,
			 avl_alloc_cb *alloc);
struct avl *avl_remove  (struct avl **root, const void *key, avl_cmp_cb *cmp);

#endif  /* CAPSA_AVL_H */
