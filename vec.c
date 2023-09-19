/*
 * Colibri Dynamic Array (Vector)
 *
 * Copyright (c) 2014-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdlib.h>

#include <data/atom.h>
#include <data/vec.h>

VEC_DECLARE_TYPED (atom, const void, const void)

int vec_expand (struct atom_vec *o)
{
	const size_t next = o->avail * 2 | 1;

	if (o->avail == ~(size_t) 0) {
		errno = ENOMEM;
		return 0;
	}

	return vec_resize (o, next);
}

int vec_resize (struct atom_vec *o, size_t next)
{
	const void **data;

	if ((data = realloc (o->data, sizeof (o->data[0]) * next)) == NULL)
		return 0;

	o->avail = next;
	o->data  = data;
	return 1;
}
