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

bool unit_vec_copy (const struct atom_vec *s, struct atom_vec *d, size_t size)
{
	if ((d->data = malloc (s->avail * size)) == NULL)
		return false;

	d->count = s->count;
	d->avail = s->avail;
	memcpy (d->data, s->data, s->count * size);
	return true;
}
