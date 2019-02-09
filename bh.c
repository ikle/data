/*
 * Simple Binary Heap with Wait Queue
 *
 * Copyright (c) 2015,2019 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <data/bh.h>

/* heap based on full binary tree packed into array */
#define root		(0)
#define left(i)		(2 * (i) + 1)
#define right(i)	(2 * (i) + 2)
#define parent(i)	(((i) - 1) / 2)

void bh_init (struct bh *bh, int (*cmp) (void *a, void *b))
{
	bh->cmp = cmp;
	bh->avail = bh->tail = bh->count = 0;
	bh->pool = NULL;
}

void bh_fini (struct bh *bh, void (*item_free) (void *o))
{
	size_t i;

	if (item_free != NULL)
		for (i = 0; i < bh->tail; ++i)
			item_free (bh->pool[i]);

	free (bh->pool);
}

void *bh_top (struct bh *bh)
{
	return (bh->count > 0) ? bh->pool[0] : NULL;
}

static int bh_resize (struct bh *bh)
{
	size_t count;
	void *pool;

	if (bh->tail < bh->avail)
		return 1;

	count = (bh->tail + 1) * 3 / 2;

	pool = realloc (bh->pool, sizeof (bh->pool[0]) * count);
	if (pool == NULL)
		return 0;

	bh->pool = pool;
	bh->avail = count;
	return 1;
}

static void bh_bubble_up (struct bh *bh, size_t i)
{
	void *x = bh->pool[i];

	for (; i > root && bh->cmp (x, bh->pool[parent (i)]); i = parent (i))
		bh->pool[i] = bh->pool[parent (i)];  /* pull down */

	bh->pool[i] = x;
}

static size_t bh_max_child (struct bh *bh, size_t i)
{
	size_t l = left (i), r = right (i);

	if (l >= bh->count)
		return SIZE_MAX;

	if (r >= bh->count)
		return l;

	return bh->cmp (bh->pool [r], bh->pool [l]) ? r : l;
}

static void bh_bubble_down (struct bh *bh, size_t i)
{
	void *x = bh->pool[i];
	size_t child;

	for (
		;
		(child = bh_max_child (bh, i)) < SIZE_MAX &&
		!bh->cmp (bh->pool [child], x);
		i = child
	)
		bh->pool[i] = bh->pool[child];  /* pull up */

	bh->pool[i] = x;
}

int bh_add (struct bh *bh, void *x)
{
	if (x == NULL || !bh_resize (bh))
		return 0;

	bh->pool[bh->tail++] = x;

	return 1;
}

void bh_commit (struct bh *bh)
{
	for (; bh->count < bh->tail; ++bh->count)
		bh_bubble_up (bh, bh->count);
}

int bh_push (struct bh *bh, void *x)
{
	if (!bh_add (bh, x))
		return 0;

	bh_commit (bh);

	return 1;
}

void *bh_pop (struct bh *bh)
{
	void *x;
	void **end;

	if (bh->count == 0)
		return NULL;

	x = bh->pool[0];

	bh->pool[0] = bh->pool[--bh->count];
	bh_bubble_down (bh, 0);

	/* move queue to rightful place */
	--bh->tail;
	end = bh->pool + bh->count;
	memmove (end, end + 1, (bh->tail - bh->count) * sizeof (*end));

	bh_commit (bh);
	return x;
}
