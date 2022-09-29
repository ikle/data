/*
 * Colibri Dynamic Array
 *
 * Copyright (c) 2017-2022 Alexei A. Smekalkine
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

void da_init (struct da *o, const struct data_type *type);
void da_fini (struct da *o);

int da_add (struct da *o, void *e);

#endif  /* COLIBRI_DATA_DA_H */
