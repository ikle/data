/*
 * Capsa Dynamic Array (Vector)
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

bool vec_expand (struct atom_vec *o, size_t size)
{
	if (o->avail == ~(size_t) 0) {
		errno = ENOMEM;
		return false;
	}

	return vec_resize (o, size, o->avail * 2 | 1);
}

bool vec_resize (struct atom_vec *o, size_t size, size_t next)
{
	const void **data;

	if (next > ~(size_t) 0 / size) {
		errno = ENOMEM;
		return false;
	}

	if ((data = realloc (o->data, size * next)) == NULL)
		return false;

	o->avail = next;
	o->data  = data;
	return true;
}
