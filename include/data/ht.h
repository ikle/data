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

void  *ht_copy (const void *from);
void   ht_free (void *o);
int    ht_eq   (const void *o, const void *sample);
size_t ht_hash (const void *o, size_t iv);

extern const struct data_type ht_type;

struct ht {
	const struct data_type *type;
	size_t count, size;
	void **table;
};

int  ht_init (struct ht *o, const struct data_type *type);
void ht_fini (struct ht *o);

enum ht_policy {
	HT_ONCE		= 0x1,
	HT_REPLACE	= 0x2,
};

size_t ht_index (const struct ht *o, const void *sample);
void *ht_lookup (const struct ht *o, const void *sample);
void *ht_insert (struct ht *o, const void *sample, int policy);
void ht_remove  (struct ht *o, const void *sample);
void ht_clean   (struct ht *o);

#define ht_foreach(i, entry, o)				\
	for ((i) = 0; (i) < (o)->size; ++(i))		\
		if (((entry) = (o)->table[i]) != NULL)

#endif  /* COLIBRI_DATA_HT_H */
