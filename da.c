/*
 * Colibri Dynamic Array
 *
 * Copyright (c) 2017-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <string.h>

#include <data/da.h>

int da_init (struct da *o, const struct data_type *type)
{
	o->type  = type;
	o->count = 0;
	o->size  = 2;

	return (o->table = calloc (o->size, sizeof (o->table[0]))) != NULL;
}

void da_fini (struct da *o)
{
	size_t i;

	for (i = 0; i < o->count; ++i)
		o->type->free (o->table[i]);

	free (o->table);
}

static int resize (struct da *o)
{
	if (o->count < o->size)
		return 1;

	const size_t size = o->size * 2;
	void **table;

	if ((table = realloc (o->table, sizeof (table[0]) * size)) == NULL)
		return 0;

	memset (table + o->size, 0, sizeof (table[0]) * o->size);

	o->size  = size;
	o->table = table;
	return 1;
}

int da_add (struct da *o, void *e)
{
	if (!resize (o))
		return 0;

	o->table[o->count++] = e;
	return 1;
}
