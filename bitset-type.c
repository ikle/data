/*
 * Capsa Compact Binary Set Type
 *
 * Copyright (c) 2007-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <string.h>

#include <data/bitset.h>
#include <capsa/hash.h>

void *bitset_copy (const void *from)
{
	const struct bitset *src = from;
	const size_t size = src->count * sizeof (src->set[0]);
	struct bitset *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->count = src->count;

	if ((o->set = malloc (size)) == NULL)
		goto no_set;

	memcpy (o->set, src->set, size);
	return o;
no_set:
	free (o);
	return NULL;
}

void bitset_free (void *o)
{
	if (o == NULL)
		return;

	bitset_fini (o);
	free (o);
}

int bitset_eq (const void *a, const void *b)
{
	const struct bitset *p = a, *q = b;

	if (p->count != q->count)
		return 0;

	return memcmp (p->set, q->set, p->count * sizeof (p->set[0])) == 0;
}

size_t bitset_hash (const void *o, size_t iv)
{
	const struct bitset *p = o;

	return hash (iv, p->set, p->count * sizeof (p->set[0]));
}

const struct data_type bitset_type = {
	.copy	= bitset_copy,
	.free	= bitset_free,
	.eq	= bitset_eq,
	.hash	= bitset_hash,
};
