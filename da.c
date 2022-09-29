/*
 * Colibri Dynamic Array
 *
 * Copyright (c) 2017-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdlib.h>

#include <data/da.h>

void da_init (struct da *o)
{
	o->count = 0;
	o->size  = 0;
	o->table = NULL;
}

void da_fini (struct da *o, void (*entry_free) (void *o))
{
	size_t i;

	for (i = 0; i < o->count; ++i)
		entry_free (o->table[i]);

	free (o->table);
}

static int resize (struct da *o)
{
	if (o->count < o->size)
		return 1;

	const size_t size = (o->size < 2) ? 2 : o->size * 2;
	void **table;

	if (sizeof (o->table[0]) * size < sizeof (o->table[0]) * o->size) {
		errno = ENOMEM;
		return 0;
	}

	if ((table = realloc (o->table, sizeof (o->table[0]) * size)) == NULL)
		return 0;

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
