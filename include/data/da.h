/*
 * Colibri Dynamic Array
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_DA_H
#define COLIBRI_DATA_DA_H  1

#include <data/type.h>

struct da {
	const struct data_type *type;
	size_t count, size;
	void **table;
};

int  da_init (struct da *da, const struct data_type *type);
void da_fini (struct da *da);

int da_add (struct da *da, void *o);

#endif  /* COLIBRI_DATA_DA_H */
