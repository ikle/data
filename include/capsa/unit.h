/*
 * Capsa Unit Types
 *
 * Copyright (c) 2017-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_UNIT_H
#define CAPSA_UNIT_H  1

#include <capsa/hash.h>

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
static inline bool name##_eq (ctype o, ctype peer)	\
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

#endif  /* CAPSA_UNIT_H */
