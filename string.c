/*
 * String Type
 *
 * Copyright (c) 2017 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include <data/hash.h>
#include <data/string.h>

int string_eq (const void *a, const void *b)
{
	return strcmp (a, b) == 0;
}

size_t string_hash (size_t iv, const void *o)
{
	return hash (iv, o, strlen (o));
}
