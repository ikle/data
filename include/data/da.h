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
	size_t count, size;
	void **table;
};

void da_init (struct da *o);
void da_fini (struct da *o, void (*entry_free) (void *o));

int da_add (struct da *o, void *e);

#endif  /* COLIBRI_DATA_DA_H */
