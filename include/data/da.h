/*
 * Colibri Dynamic Array
 *
 * Copyright (c) 2017-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_DA_H
#define COLIBRI_DATA_DA_H  1

#include <stddef.h>

struct da {
	size_t count, avail;
	void **data;
};

void da_init (struct da *o);
void da_fini (struct da *o, void free (void *o));

int da_append (struct da *o, void *e);
int da_insert (struct da *o, size_t i, void *e, void free (void *o));

#endif  /* COLIBRI_DATA_DA_H */
