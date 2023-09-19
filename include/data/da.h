/*
 * Colibri Dynamic Array
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_DA_H
#define COLIBRI_DATA_DA_H  1

#include <stdbool.h>
#include <stddef.h>

struct da {
	size_t count, avail;
	void **data;
};

static inline void da_init (struct da *o)
{
	o->count = 0;
	o->avail = 0;
	o->data  = NULL;
}

static inline void da_fini (struct da *o, void entry_free (void *o))
{
	size_t i;

	for (i = 0; i < o->count; ++i)
		entry_free (o->data[i]);

	free (o->data);
}

bool da_append (struct da *o, void *e);

static inline
bool da_insert (struct da *o, size_t i, void *e, void entry_free (void *o))
{
	entry_free (o->data[i]);
	o->data[i] = e;
	return true;
}

#endif  /* COLIBRI_DATA_DA_H */
