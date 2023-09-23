/*
 * Capsa Dynamic Array (Vector) Resizer
 *
 * Copyright (c) 2014-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "vec-resize.h"

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
