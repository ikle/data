/*
 * Capsa Dynamic Array (Vector) Resizer
 *
 * Copyright (c) 2014-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "vec-resize.h"

bool vec_expand (struct atom_vec *o, size_t size)
{
	if (o->avail == ~(size_t) 0) {
		errno = ENOMEM;
		return false;
	}

	return vec_resize (o, size, o->avail * 2 | 1);
}
