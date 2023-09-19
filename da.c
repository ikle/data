/*
 * Colibri Dynamic Array
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdlib.h>

#include <data/da.h>

static int da_resize (struct da *o, size_t next)
{
	void **data;

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

int da_append (struct da *o, void *e)
{
	if (o->count >= o->avail && !da_resize (o, o->avail * 2 | 1))
		return 0;

	o->data[o->count++] = e;
	return 1;
}
