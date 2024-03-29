/*
 * Capsa Constant String Type
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_LABEL_H
#define CAPSA_LABEL_H  1

#include <capsa/hash.h>
#include <string.h>

static inline void label_free (const char *o)
{
	/* nothing */
}

static inline bool label_copy (const char *const *s, const char **d)
{
	*d = *s;
	return true;
}

static inline bool label_eq (const char *o, const char *peer)
{
	return strcmp (o, peer) == 0;
}

static inline int label_cmp (const char *o, const char *peer)
{
	return strcoll (o, peer);
}

static inline size_t label_hash (const char *o, size_t iv)
{
	return hash (iv, o, strlen (o));
}

#endif  /* CAPSA_LABEL_H */
