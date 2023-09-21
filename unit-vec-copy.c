/*
 * Capsa Unit Vector Copy Constructor
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <capsa/atom.h>
#include <capsa/vec.h>

#include <stdlib.h>
#include <string.h>

VEC_DECLARE_TYPED (atom, const void *, const void *)

void *unit_vec_copy (const struct atom_vec *o, size_t size)
{
	struct atom_vec *copy;

	if ((copy = atom_vec_alloc ()) == NULL)
		return copy;

	if ((copy->data = malloc (o->avail * size)) == NULL)
		goto no_data;

	copy->count = o->count;
	copy->avail = o->avail;
	memcpy (copy->data, o->data, o->count * size);
	return copy;
no_data:
	atom_vec_free (copy);
	return NULL;
}
