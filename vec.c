/*
 * Colibri Dynamic Array (Vector)
 *
 * Copyright (c) 2014-2022 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <data/atom.h>
#include <data/vec.h>

VEC_DECLARE_TYPED (atom, const void, const void)

int vec_resize (struct atom_vec *o, size_t next)
{
	const void **data;

	if (sizeof (o->data[0]) * next < sizeof (o->data[0]) * o->avail) {
		errno = ENOMEM;
		return 0;
	}

	if ((data = realloc (o->data, sizeof (o->data[0]) * next)) == NULL)
		return 0;

	o->avail = next;
	o->data  = data;
	return 1;
}

static size_t get_bound (size_t x)
{
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;

#if SIZE_MAX > 65535
	x |= x >> 16;
#if SIZE_MAX > 4294967295L
	x |= x >> 32;
#endif
#endif
	return x;
}

int vec_expand (struct atom_vec *o, size_t i)
{
	const size_t count = i + 1;

	if (i < o->count)
		return 1;

	if (i >= o->avail && !vec_resize (o, get_bound (count)))
		return 0;

	memset (o->data + sizeof (o->data[0]) * o->count, 0,
		sizeof (o->data[0]) * (count - o->count));

	o->count = count;
	return 1;
}
