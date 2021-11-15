/*
 * Colobri String Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <string.h>

#include <data/hash.h>
#include <data/string.h>

void *string_copy (const void *from)
{
	return strdup (from);
}

int string_eq (const void *a, const void *b)
{
	return strcmp (a, b) == 0;
}

size_t string_hash (size_t iv, const void *o)
{
	return hash (iv, o, strlen (o));
}

const struct data_type string_type = {
	.copy	= string_copy,
	.free	= free,
	.eq	= string_eq,
	.hash	= string_hash,
};
