/*
 * Capsa Dynamic Array (Vector) Resizer
 *
 * Copyright (c) 2014-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef VEC_RESIZE_H
#define VEC_RESIZE_H  1

#include <capsa/atom.h>
#include <capsa/vec.h>

#include <errno.h>
#include <stdlib.h>

VEC_DECLARE_TYPED (atom, const void *, const void *);

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

#endif  /* VEC_RESIZE_H */
