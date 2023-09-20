/*
 * Capsa Binary Vector
 *
 * Copyright (c) 2007-2023 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CAPSA_BITVEC_H
#define CAPSA_BITVEC_H  1

#include <capsa/types.h>
#include <string.h>

static inline size_t bitvec_len (size_t width)
{
	const size_t size = sizeof (long) * CHAR_BIT;

	return (width + size - 1) / size;
}

static inline void bitvec_zero (long *o, size_t len)
{
	memset (o, 0, len * sizeof (o[0]));
}

static inline bool bitvec_test (const long *o, size_t i)
{
	const size_t size = sizeof (o[0]) * CHAR_BIT;
	const size_t pos = i / size;
	const size_t bit = i % size;

	return (o[pos] & (1UL << bit)) != 0;
}

#define BITVEC_BIT_OP(name, op)						\
									\
static inline long bitvec_slot_##name (long x, long m) { return op; }	\
									\
static inline void bitvec_##name (long *o, size_t i)			\
{									\
	const size_t size = sizeof (o[0]) * CHAR_BIT;			\
	const size_t pos = i / size;					\
	const size_t bit = i % size;					\
									\
	o[pos] = bitvec_slot_##name (o[pos], 1UL << bit);		\
}

BITVEC_BIT_OP (add,    x | m)		/* o = o ∪ {i} */
BITVEC_BIT_OP (del,    x & ~m)		/* o = o \ {i} */
BITVEC_BIT_OP (toggle, x ^ m)		/* o = o ∆ {i} */

#define BITVEC_BINARY_OP(name, op)					\
									\
static inline long bitvec_slot_##name (long x, long y) { return op; }	\
									\
static inline								\
void bitvec_##name (long *r, const long *x, const long *y, size_t len)	\
{									\
	size_t i;							\
									\
	for (i = 0; i < len; ++i)					\
		r[i] = bitvec_slot_##name (x[i], y[i]);			\
}

BITVEC_BINARY_OP (join, x | y)		/* r = x ∪ y */
BITVEC_BINARY_OP (meet, x & y)		/* r = x ∩ y */
BITVEC_BINARY_OP (impl, ~x | y)		/* r = x → y */
BITVEC_BINARY_OP (diff, x & ~y)		/* r = x \ y */
BITVEC_BINARY_OP (xor,  x ^ y)		/* r = x ∆ y */

#endif  /* CAPSA_BITVEC_H */
