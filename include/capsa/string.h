/*
 * Capsa String Type
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_STRING_H
#define CAPSA_STRING_H  1

#include <stdlib.h>
#include <string.h>

#include <capsa/hash.h>

static inline void string_free (char *o)
{
	free (o);
}

static inline char *string_copy (const char *o)
{
	return strdup (o);
}

static inline int string_eq (const char *o, const char *peer)
{
	return strcmp (o, peer) == 0;
}

static inline int string_cmp (const char *o, const char *peer)
{
	return strcoll (o, peer);
}

static inline size_t string_hash (const char *o, size_t iv)
{
	return hash (iv, o, strlen (o));
}

#endif  /* CAPSA_STRING_H */
