/*
 * Colibry Unit Types
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_UNIT_H
#define COLIBRI_DATA_UNIT_H  1

#include <data/hash.h>

#define UNIT_DECLARE_TYPED(name, type, ctype, intfit)	\
							\
static inline void name##_free (type o)			\
{							\
	/* nothing */					\
}							\
							\
static inline type name##_copy (ctype o)		\
{							\
	return o;					\
}							\
							\
static inline int name##_eq (ctype o, ctype peer)	\
{							\
	return o == peer;				\
}							\
							\
static inline int name##_cmp (ctype o, ctype peer)	\
{							\
	return intfit ? o - peer :			\
	       o < peer ? -1 : o > peer ? 1 : 0;	\
}							\
							\
static inline size_t name##_hash (ctype o, size_t iv)	\
{							\
	return hash (iv, &o, sizeof (o));		\
}

#endif  /* COLIBRI_DATA_UNIT_H */