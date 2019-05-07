/*
 * Small Allocator
 *
 * Copyright (c) 2008-2010,2019 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <data/sa.h>

#define REST(order)		((1 << (order)) - 1)
#define ALIGN(x, order)		(((x) + REST (order)) & ~REST (order))

struct sa_block {
	struct sa_block *next;
	char data[8];
};

static struct sa_block *alloc_block (struct sa_pool *o)
{
	struct sa_block *p;

	if ((p = malloc (o->size)) == NULL)
		return NULL;

	p->next = NULL;
	return p;
}

static int expand (struct sa_pool *o, size_t size)
{
	size_t start;

	if ((o->end + size) < o->size)
		return 1;

	start = ALIGN (offsetof (struct sa_block, data), o->order);

	if ((start + size) > o->size) {
		errno = EINVAL;
		return 0;
	}

	if (o->tail->next == NULL && (o->tail->next = alloc_block (o)) == NULL)
		return 0;

	o->tail = o->tail->next;
	o->end = start;
	return 1;
}

int sa_pool_init (struct sa_pool *o, size_t size, int order)
{
	if (size < sizeof (*o->head)) {
		errno = EINVAL;
		return 0;
	}

	o->size  = size == 0 ? BUFSIZ : size;
	o->order = order < 0 ? 3 : order;

	o->head = o->tail = alloc_block (o);
	o->end = ALIGN (offsetof (struct sa_block, data), o->order);

	return o->head != NULL;
}

void sa_pool_fini (struct sa_pool *o)
{
	struct sa_block *p, *next;

	for (p = o->head; p != NULL; p = next) {
		next = p->next;
		free (p);
	}
}

void *sa_alloc (struct sa_pool *o, size_t size)
{
	void *p;

	if (!expand (o, size))
		return NULL;

	p = (char *) o->tail + o->end;
	o->end = ALIGN (o->end + size, o->order);

	return p;
}
