/*
 * Simple Binary Heap with Wait Queue
 *
 * Copyright (c) 2015-2023 Alexei A. Smekalkine
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

void bh_init (struct bh *o, int (*gt) (const void *a, const void *b))
{
	o->gt    = gt;
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
	size_t next = (o->avail < 8) ? 8 : o->avail * 2;
	void *pool;

	if (o->tail < o->avail)
		return 1;

	if (sizeof (o->pool[0]) * next < sizeof (o->pool[0]) * o->avail) {
		errno = ENOMEM;
		return 0;
	}

	if ((pool = realloc (o->pool, sizeof (o->pool[0]) * next)) == NULL)
		return 0;

	o->pool  = pool;
	o->avail = next;
	return 1;
}

static void bh_bubble_up (struct bh *o, size_t i)
{
	void *x = o->pool[i];

	for (; i > root && o->gt (x, o->pool[parent (i)]); i = parent (i))
		o->pool[i] = o->pool[parent (i)];  /* pull down */

	o->pool[i] = x;
}

static size_t bh_max_child (struct bh *o, size_t i)
{
	size_t l = left (i), r = right (i);

	return	l >= o->count ? 0 :  /* root cannot be child of any node */
		r >= o->count ? l :
		o->gt (o->pool [l], o->pool [r]) ? l : r;
}

static void bh_bubble_down (struct bh *o, size_t i)
{
	void *x = o->pool[i];
	size_t child;

	for (
		;
		(child = bh_max_child (o, i)) != 0 &&
		o->gt (o->pool [child], x);
		i = child
	)
		o->pool[i] = o->pool[child];  /* pull up */

	o->pool[i] = x;
}

void bh_commit (struct bh *o)
{
	for (; o->count < o->tail; ++o->count)
		bh_bubble_up (o, o->count);
}

int bh_push (struct bh *o, void *x, int nowait)
{
	if (o->tail >= o->avail && (nowait || !bh_resize (o)))
		return 0;

	o->pool[o->tail++] = x;

	if (!nowait)
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

	o->pool[0] = o->pool[o->tail = --o->count];
	bh_bubble_down (o, 0);
	return x;
}
