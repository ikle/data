/*
 * Colibri Opening Addressing Hash Table Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include <data/ht.h>

void *ht_copy (const void *from)
{
	const struct ht *src = from;
	struct ht *o;
	size_t i;
	void *entry;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	ht_init (o, src->type);

	ht_foreach (i, entry, src)
		o->table[i] = o->type->copy (entry);

	return o;
}

void ht_free (void *o)
{
	if (o == NULL)
		return;

	ht_fini (o);
	free (o);
}

int ht_eq (const void *a, const void *b)
{
	const struct ht *p = a, *q = b;
	size_t i;
	void *entry;

	if (p->count != q->count || p->type != q->type)
		return 0;

	ht_foreach (i, entry, p)
		if (!p->type->eq (entry, ht_lookup (q, entry)))
			return 0;

	return 1;
}

size_t ht_hash (const void *o, size_t iv)
{
	const struct ht *p = o;
	size_t i;
	void *entry;

	/*
	 * Calculate order-independed hash from entries order
	 */
	ht_foreach (i, entry, p)
		iv ^= p->type->hash (entry, 0);

	return iv;
}

const struct data_type ht_type = {
	.copy	= ht_copy,
	.free	= ht_free,
	.eq	= ht_eq,
	.hash	= ht_hash,
};
