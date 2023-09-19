/*
 * Colibry Integer Type
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_INT_H
#define COLIBRI_DATA_INT_H  1

#include <data/hash.h>

static inline void int_free (int o)
{
	/* nothing */
}

static inline int int_copy (int o)
{
	return o;
}

static inline int int_eq (int o, int peer)
{
	return o == peer;
}

static inline int int_cmp (int o, int peer)
{
	return o - peer;
}

static inline size_t int_hash (int o, size_t iv)
{
	return hash (iv, &o, sizeof (o));
}

#endif  /* COLIBRI_DATA_INT_H */
