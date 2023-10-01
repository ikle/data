/*
 * AVL Tree Walk
 *
 * Copyright (c) 2010-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <capsa/avl.h>

void avl_walk (struct avl *o, avl_walk_cb *poke, void *cookie)
{
	if (o == NULL)
		return;

	avl_walk (o->child[0], poke, cookie);
	poke (o, cookie);
	avl_walk (o->child[1], poke, cookie);
}
