/*
 * Opening Addressing Hash Table
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_HT_H
#define COLIBRI_DATA_HT_H  1

#include <data/type.h>

struct ht {
	const struct data_type *type;
	size_t count, size;
	void **table;
};

int  ht_init (struct ht *ht, const struct data_type *type);
void ht_fini (struct ht *ht);

int ht_eq (const void *o, const void *sample);
size_t ht_hash (size_t iv, const void *o);

size_t ht_index (const struct ht *ht, const void *o);
void *ht_lookup (const struct ht *ht, const void *o);
int ht_insert (struct ht *ht, void *o, int replace);
void ht_remove (struct ht *ht, const void *o);
void ht_clean (struct ht *ht);

#define ht_foreach(i, o, ht)				\
	for ((i) = 0; (i) < (ht)->size; ++(i))		\
		if (((o) = (ht)->table[i]) != NULL)

#endif  /* COLIBRI_DATA_HT_H */
