/*
 * AVL Tree Find
 *
 * Copyright (c) 2010-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <capsa/avl.h>

struct avl *avl_find (struct avl **root, const void *key, avl_cmp_cb *cmp)
{
	struct avl *o;
	int c;

	for (o = *root; o != NULL; o = o->child[c > 0])
		if ((c = cmp (key, o)) == 0)
			return o;

	return o;
}
