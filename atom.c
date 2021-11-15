/*
 * Colobri Atom Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include <data/hash.h>
#include <data/atom.h>

void *atom_copy (const void *from)
{
	return (void *) from;
}

void atom_free (void *o)
{
	/* nothing */
}

int atom_eq (const void *a, const void *b)
{
	return strcmp (a, b) == 0;
}

size_t atom_hash (size_t iv, const void *o)
{
	return hash (iv, o, strlen (o));
}

const struct data_type atom_type = {
	.copy	= atom_copy,
	.free	= atom_free,
	.eq	= atom_eq,
	.hash	= atom_hash,
};
