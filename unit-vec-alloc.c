/*
 * Capsa Unit Vector Allocator
 *
 * Copyright (c) 2014-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <capsa/atom.h>
#include <capsa/vec.h>

#include <stdlib.h>

VEC_DECLARE_TYPED (atom, const void *, const void *)

void *vec_alloc (void)
{
	struct atom_vec *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return o;

	atom_vec_init (o);
	return o;
}
