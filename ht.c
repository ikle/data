/*
 * Colibri Opening Addressing Hash Table
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdlib.h>

#include <data/ht.h>

int ht_init (struct ht *o, const struct data_type *type)
{
	if (type == NULL || type->hash == NULL) {
		errno = EINVAL;
		return 0;
	}

	o->type  = type;
	o->count = 0;
	o->size  = 4;

	return (o->table = calloc (o->size, sizeof (o->table[0]))) != NULL;
}

void ht_fini (struct ht *o)
{
	size_t i;

	for (i = 0; i < o->size; ++i)
		o->type->free (o->table[i]);
}

static size_t get_slot (const struct data_type *type, size_t size,
			void **table, const void *o)
{
	const size_t mask = size - 1;  /* size MUST be power of two */
	size_t i;

	for (
		i = type->hash (0, o) & mask;
		table[i] != NULL && !type->eq (table[i], o);
		i = (i + 1) & mask
	) {}

	return i;
}

size_t ht_index (const struct ht *o, const void *sample)
{
	return get_slot (o->type, o->size, o->table, sample);
}

void *ht_lookup (const struct ht *o, const void *sample)
{
	return o->table[ht_index (o, sample)];
}

static int resize (struct ht *o)
{
	if (o->count <= o->size / 2)  /* load factor <= 50% */
		return 1;

	const size_t size = o->size * 2;
	void **table;
	size_t i;
	void *entry;

	if ((table = calloc (size, sizeof (table[0]))) == NULL)
		return 0;

	ht_foreach (i, entry, o)
		table[get_slot (o->type, size, table, entry)] = entry;

	free (o->table);

	o->size  = size;
	o->table = table;
	return 1;
}

void *ht_insert (struct ht *o, const void *sample, int replace)
{
	size_t i;
	void *entry;

	if (!resize (o))
		return NULL;

	i = ht_index (o, sample);

	if (o->table[i] != NULL && !replace) {
		errno = EEXIST;
		return NULL;
	}

	if ((entry = o->type->copy (sample)) == NULL)
		return NULL;

	if (o->table[i] != NULL)
		o->type->free (o->table[i]);
	else
		++o->count;

	return o->table[i] = entry;
}

void ht_remove (struct ht *o, const void *sample)
{
	size_t i = ht_index (o, sample);

	if (o->table[i] == NULL)
		return;

	o->type->free (o->table[i]);
	o->table[i] = NULL;
	--o->count;
}

void ht_clean (struct ht *o)
{
	size_t i;

	ht_fini (o);

	for (i = 0; i < o->size; ++i)
		o->table[i] = NULL;
}
