/*
 * Capsa Constant String Type
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_LABEL_H
#define CAPSA_LABEL_H  1

#include <string.h>

#include <capsa/hash.h>

static inline void label_free (const char *o)
{
	/* nothing */
}

static inline const char *label_copy (const char *o)
{
	return o;
}

static inline int label_eq (const char *o, const char *peer)
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