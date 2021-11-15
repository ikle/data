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
	void *item;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	ht_init (o, src->type);

	ht_foreach (i, item, src)
		o->table[i] = o->type->copy (item);

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
	const struct ht *p = a;
	const struct ht *q = b;
	size_t i;
	void *item;

	if (p->count != q->count || p->type != q->type)
		return 0;

	ht_foreach (i, item, p)
		if (!p->type->eq (item, ht_lookup (q, item)))
			return 0;

	return 1;
}

size_t ht_hash (size_t iv, const void *o)
{
	const struct ht *p = o;
	size_t i;
	void *item;

	/* NOTE: we need to calculate order-independed hash from items */

	ht_foreach (i, item, p)
		iv = p->type->hash (iv, item);

	return iv;
}

const struct data_type ht_type = {
	.copy	= ht_copy,
	.free	= ht_free,
	.eq	= ht_eq,
	.hash	= ht_hash,
};
