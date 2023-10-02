/*
 * AVL Tree Cardinality Counter
 *
 * Copyright (c) 2010-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <capsa/avl.h>

size_t avl_count (struct avl *o)
{
	return	o == NULL ? 0 :
		avl_count (o->child[0]) + 1 + avl_count (o->child[1]);
}
