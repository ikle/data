/*
 * Small Allocator
 *
 * Copyright (c) 2008-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdlib.h>

#include <data/sa.h>

#ifdef __BIGGEST_ALIGNMENT__
#define DEF_ALIGNMENT	__BIGGEST_ALIGNMENT__
#else
#define DEF_ALIGNMENT	sizeof (long double)
#endif

#define SA_ALIGN(x, mask)	(((x) + mask) & ~mask)
#define SA_BLOCK_SIZE		4096

struct sa_block {
	struct sa_block *next;
	char data[8];
};

static struct sa_block *sa_block_alloc (void)
{
	struct sa_block *o;

	if ((o = malloc (SA_BLOCK_SIZE)) == NULL)
		return o;

	o->next = NULL;
	return o;
}

struct sa_pool {
	struct sa_block *head, *tail;
	size_t mask, end;
};

static int expand (struct sa_pool *o, size_t size)
{
	size_t start;

	if ((o->end + size) <= SA_BLOCK_SIZE)
		return 1;

	start = SA_ALIGN (offsetof (struct sa_block, data), o->mask);

	if ((start + size) > SA_BLOCK_SIZE) {
		errno = EOVERFLOW;
		return 0;
	}

	if (o->tail->next == NULL &&
	    (o->tail->next = sa_block_alloc ()) == NULL)
		return 0;

	o->tail = o->tail->next;
	o->end  = start;
	return 1;
}

struct sa_pool *sa_pool_alloc (unsigned align)
{
	struct sa_pool *o;

	if (align == 0)
		align = DEF_ALIGNMENT;

	if ((align & (align - 1)) != 0) {  /* align MUST be power of two */
		errno = EINVAL;
		return NULL;
	}

	if ((o = malloc (sizeof (*o))) == NULL)
		return o;

	if ((o->head = sa_block_alloc ()) == NULL)
		goto no_block;

	o->tail = o->head;
	o->mask = align - 1;
	o->end  = SA_ALIGN (offsetof (struct sa_block, data), o->mask);
	return o;
no_block:
	free (o);
	return NULL;
}

void sa_pool_free (struct sa_pool *o)
{
	struct sa_block *p, *next;

	if (o == NULL)
		return;

	for (p = o->head; p != NULL; p = next) {
		next = p->next;
		free (p);
	}

	free (o);
}

void *sa_alloc (struct sa_pool *o, size_t size)
{
	void *p;

	if (!expand (o, size))
		return NULL;

	p = (void *) o->tail + o->end;
	o->end = SA_ALIGN (o->end + size, o->mask);
	return p;
}
