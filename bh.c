/*
 * Simple Binary Heap with Wait Queue
 *
 * Copyright (c) 2015-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#include <data/bh.h>

/* heap based on full binary tree packed into array */
#define root		(0)
#define left(i)		(2 * (i) + 1)
#define right(i)	(2 * (i) + 2)
#define parent(i)	(((i) - 1) / 2)

void bh_init (struct bh *o, int (*cmp) (void *a, void *b))
{
	o->cmp   = cmp;
	o->avail = o->tail = o->count = 0;
	o->pool  = NULL;
}

void bh_fini (struct bh *o, void (*item_free) (void *o))
{
	size_t i;

	if (item_free != NULL)
		for (i = 0; i < o->tail; ++i)
			item_free (o->pool[i]);

	free (o->pool);
}

void *bh_top (struct bh *o)
{
	return (o->count > 0) ? o->pool[0] : NULL;
}

static int bh_resize (struct bh *o)
{
	size_t count;
	void *pool;

	if (o->tail < o->avail)
		return 1;

	if ((count = (o->tail < 8) ? 8 : o->tail * 2) < o->tail) {
		errno = ERANGE;
		count = SIZE_MAX;
	}

	if ((pool = realloc (o->pool, sizeof (o->pool[0]) * count)) == NULL)
		return 0;

	o->pool  = pool;
	o->avail = count;
	return o->tail < o->avail;
}

static void bh_bubble_up (struct bh *o, size_t i)
{
	void *x = o->pool[i];

	for (; i > root && o->cmp (x, o->pool[parent (i)]); i = parent (i))
		o->pool[i] = o->pool[parent (i)];  /* pull down */

	o->pool[i] = x;
}

static size_t bh_max_child (struct bh *o, size_t i)
{
	size_t l = left (i), r = right (i);

	return	l >= o->count ? 0 :  /* root cannot be child of any node */
		r >= o->count ? l :
		o->cmp (o->pool [l], o->pool [r]) ? l : r;
}

static void bh_bubble_down (struct bh *o, size_t i)
{
	void *x = o->pool[i];
	size_t child;

	for (
		;
		(child = bh_max_child (o, i)) != 0 &&
		!o->cmp (x, o->pool [child]);
		i = child
	)
		o->pool[i] = o->pool[child];  /* pull up */

	o->pool[i] = x;
}

int bh_add (struct bh *o, void *x)
{
	if (!bh_resize (o))
		return 0;

	o->pool[o->tail++] = x;
	return 1;
}

void bh_commit (struct bh *o)
{
	for (; o->count < o->tail; ++o->count)
		bh_bubble_up (o, o->count);
}

int bh_push (struct bh *o, void *x)
{
	if (!bh_add (o, x))
		return 0;

	bh_commit (o);
	return 1;
}

void *bh_pop (struct bh *o)
{
	void *x;

	bh_commit (o);

	if (o->count == 0)
		return NULL;

	x = o->pool[0];

	o->pool[0] = o->pool[--o->count];
	bh_bubble_down (o, 0);
	return x;
}
