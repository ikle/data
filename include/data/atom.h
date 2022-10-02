/*
 * Colibry Atom Type
 *
 * Copyright (c) 2017-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_ATOM_H
#define COLIBRI_DATA_ATOM_H  1

#include <data/hash.h>
#include <data/type.h>

/*
 * An atom is a pointer. It can be used, for example, to store constant
 * strings, where two identical strings with different pointers cannot
 * exist.
 */

static inline void atom_free (const void *o)
{
	/* nothing */
}

static inline const void *atom_copy (const void *o)
{
	return o;
}

static inline int atom_eq (const void *o, const void *peer)
{
	return o == peer;
}

static inline int atom_cmp (const void *o, const void *peer)
{
	return o - peer;
}

static inline size_t atom_hash (const void *o, size_t iv)
{
	return hash (iv, &o, sizeof (o));
}

const struct data_type atom_type;

#endif  /* COLIBRI_DATA_ATOM_H */
