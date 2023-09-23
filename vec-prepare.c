/*
 * Capsa Dynamic Array (Vector) Resizer
 *
 * Copyright (c) 2014-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <capsa/atom.h>
#include <capsa/vec.h>

#include <errno.h>
#include <stdlib.h>

VEC_DECLARE_TYPED (atom, const void *, const void *)

static bool vec_resize_nc (struct atom_vec *o, size_t size, size_t next)
{
	const void **data;

	if ((data = realloc (o->data, size * next)) == NULL)
		return false;

	o->avail = next;
	o->data  = data;
	return true;
}

static bool vec_resize (struct atom_vec *o, size_t size, size_t next)
{
	if (next > ~(size_t) 0 / size) {
		errno = ENOMEM;
		return false;
	}

	return vec_resize_nc (o, size, next);
}

static size_t size_bound (size_t i)  /* round up to nearest 2^n-1 */
{
	i |= i >> 1;
	i |= i >> 2;
	i |= i >> 4;
	i |= i >> 8;
#if SIZE_MAX > 65535UL
	i |= i >> 16;
#if SIZE_MAX > 4294967295ULL
	i |= i >> 32;
#endif
#endif
	return i;
}

bool vec_prepare (struct atom_vec *o, size_t size, size_t i)
{
	if (i == ~(size_t) 0) {
		errno = ENOMEM;
		return false;
	}

	return vec_resize (o, size, size_bound (i + 1));
}
