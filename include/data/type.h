/*
 * Data Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_TYPE_H
#define COLIBRI_DATA_TYPE_H  1

#include <stddef.h>

typedef void  *copy_fn (const void *from);
typedef void   free_fn (void *o);
typedef int    eq_fn   (const void *o, const void *peer);
typedef size_t hash_fn (const void *o, size_t iv);

struct data_type {
	copy_fn *copy;
	free_fn *free;
	eq_fn   *eq;
	hash_fn *hash;
};

#endif  /* COLIBRI_DATA_TYPE_H */
