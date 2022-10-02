/*
 * Colibry String Type
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_STRING_H
#define COLIBRI_DATA_STRING_H  1

#include <stdlib.h>
#include <string.h>

#include <data/hash.h>
#include <data/type.h>

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

const struct data_type string_type;

struct string;

#endif  /* COLIBRI_DATA_STRING_H */
